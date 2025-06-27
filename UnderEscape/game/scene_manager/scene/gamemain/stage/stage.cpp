#include "stage.h"
#include "../character/character.h"
#include "../enemy_manager/enemy_manager.h"
#include "blockmanager/blockmanager.h"
#include "groundmanager/groundmanager.h"
#include "wallmanager/wallmanager.h"

const float Stage::wall_width = 200.0f;
const float Stage::wall_height = 200.0f;
unsigned int Stage::wall_color = 0xff000000;

const float	Stage::walk_speed = Character::GetInstance().GetWalk();
const float	Stage::dash_speed = Character::GetInstance().GetDash();
const float	Stage::sneak_speed = Character::GetInstance().GetSneak();

const float Stage::round_width = vivid::WINDOW_WIDTH;

vivid::Vector2 Stage::start_pos = { 0.0f, vivid::WINDOW_HEIGHT - 300.0f };
vivid::Vector2 Stage::goal_pos = { Stage::round_width * 3 , vivid::WINDOW_HEIGHT - 300.0f };


const int Stage::g_map_chip_size = 100;
//const int Stage::g_map_chip_count_width = 40;
//const int Stage::g_map_chip_count_height = 11;

Stage& Stage::GetInstance(void)
{
	static Stage	instance;
	return instance;
}

void Stage::Initialize(void)
{

	//ファイル操作

	FILE* fp = nullptr;
	// ファイルを開く 
	fopen_s(&fp, "data\\map.csv", "r");
	// サイズを調べる 
	fseek(fp, 0, SEEK_END);
	int size = ftell(fp);
	fseek(fp, 0, SEEK_SET);
	// サイズ分だけ入れ物を用意する(一時的なデータ) 
	char* buf = new char[size];
	// データ(CSVファイル内の文字列)を読み込む 
	fread(buf, size, 1, fp);
	// ファイルを閉じる
	fclose(fp);

	//データ解析

		// データのサイズ分繰り返し 
	for (int i = 0, k = 0; i < size; ++i)
	{
		// 文字の0～3であれば数値に変換する 
		if (buf[i] >= '0' && buf[i] <= '8')
		{
			char t = buf[i];
			g_Map[k / g_map_chip_count_width][k % g_map_chip_count_width] =
				(MAP_CHIP_ID)atoi(&t);
			++k;
		}
	}
	// 一時的なデータを削除 
	delete[] buf;
	

	for (int y = g_map_chip_count_height-1; y >=0; y--)
	{
		for (int x = 0; x < g_map_chip_count_width; x++)
		{
			if (g_map_flg[y][x])
			{
				g_map_flg[y][x] = false;
				switch (g_Map[y][x])
				{
				case Stage::MAP_CHIP_ID::EMPTY:
					break;
				case Stage::MAP_CHIP_ID::GROUND:
				case Stage::MAP_CHIP_ID::BLOCK:
				case Stage::MAP_CHIP_ID::WALL:
					GenerateObject(x, y, (int)g_Map[y][x]);
					break;
				case Stage::MAP_CHIP_ID::ENEMY_AREA:
					g_map_flg[y][x] = true;
					break;
				case Stage::MAP_CHIP_ID::R_ENEMY:
				case Stage::MAP_CHIP_ID::L_ENEMY:
					GenerateEnemy(x, y, (int)g_Map[y][x]);
				case Stage::MAP_CHIP_ID::START:
					start_pos = { (float)(x * g_map_chip_size),((y+1) * g_map_chip_size)-Character::GetInstance().GetCharaHeight()};
					break;
				case Stage::MAP_CHIP_ID::GOAL:
					goal_pos = { (float)(x * g_map_chip_size),((y + 1) * g_map_chip_size) - Character::GetInstance().GetCharaHeight() };
					break;
				default:
					break;
				}
			}
		}
	}






	max_round = 3;
	int n = 0;
	for (int i = 0; i < max_round; i++)
	{
		round_pos[i].x = n;
		n += round_width;
		round_pos[i].y = vivid::WINDOW_HEIGHT - 300.0f;
	}
	wall_pos.y = round_pos[0].y - wall_height;
	wall_pos.x = 400;

	WallManager::GetInstance().GenerateWall(wall_pos,wall_height,wall_width,wall_color);
	sc_speed = walk_speed;
}

void Stage::Update(void)
{
	WallManager::GetInstance().Update();
	WallManager::GetInstance().Input_scroll(round_pos[0].x);
}

void Stage::Draw(void)
{
	for (int i = 0; i < max_round; i++)
	{
		vivid::DrawTexture("data\\round_box.png", round_pos[i]);
	}
	WallManager::GetInstance().Draw();
}

void Stage::Finalize(void)
{
}

void Stage::ScrollStage(void)
{
	//keyboardネームスペースの宣言
	namespace keyboard = vivid::keyboard;

	//通常時はスクロール速度が通常速度になる
	sc_speed = walk_speed;
	//左SHIFTを押している間はスクロール速度がダッシュ速度になる
	if (keyboard::Button(keyboard::KEY_ID::LSHIFT))
	{
		sc_speed = dash_speed;
	}
	//左CTRLを押している間はスクロール速度が歩行速度になる
	if (keyboard::Button(keyboard::KEY_ID::LCONTROL))
	{
		sc_speed = sneak_speed;
	}

	//左方向へのスクロール処理
	if (keyboard::Button(keyboard::KEY_ID::A))
	{
		//背景のスクロールの処理
		for (int i = 0; i < max_round; i++)
		{
			round_pos[i].x = round_pos[i].x + sc_speed;
			if (round_pos[i].x > round_width)
			{
				round_pos[i].x = -round_width - (round_width - round_pos[i].x);
			}
		}
	}
	//右方向へのスクロール処理
	if (keyboard::Button(keyboard::KEY_ID::D))
	{
		//背景の右スクロール処理
		for (int i = 0; i < max_round; i++)
		{
			round_pos[i].x = round_pos[i].x - sc_speed;
			if (round_pos[i].x < -round_width) {
				round_pos[i].x = round_width - (-round_width - round_pos[i].x);
			}
		}
	}
}

void Stage::GenerateObject(int x, int y, int Object_ID)
{
	MAP_CHIP_ID Ob_ID = (MAP_CHIP_ID)Object_ID;
	int i = 0; int n = 0;
	for (bool loop_flg = true; loop_flg;)
	{
		bool y_flg = false; bool x_flg = false;
		for (int j = x; j <= x+n; j++)
			if (g_Map[y - i - 1][j] != Ob_ID)
				y_flg = true;

		if (y_flg == false)
		{
			i++;
			for (int j = x; j <= x + n; j++)
				g_map_flg[y - i][j] = false;
		}

		for (int j = x; j <= x + n; j++)
			if (g_Map[y - i][x + n + 1] != Ob_ID)
				x_flg = true;

		if (x_flg == false)
		{
			n++;
			for (int j = x; j <= x + n; j++)
				g_map_flg[y - i][x + n] = false;
		}

		if (y_flg && x_flg)
			loop_flg = false;
	}
	vivid::Vector2 ob_pos = { (float)(x * g_map_chip_size),(float)((y - i) * g_map_chip_size) };
	int y_size = i * g_map_chip_size;
	int x_size = n * g_map_chip_size;

	switch (Ob_ID)
	{
	case Stage::MAP_CHIP_ID::GROUND:
		GroundManager::GetInstance().GenerateGround(ob_pos, y_size, x_size);
		break;
	case Stage::MAP_CHIP_ID::BLOCK:
		BlockManager::GetInstance().GenerateBlock(ob_pos, y_size, x_size);
		break;
	case Stage::MAP_CHIP_ID::WALL:
		WallManager::GetInstance().GenerateWall(ob_pos, y_size, x_size);
		break;
	default:
		break;
	}
}

void Stage::GenerateEnemy(int x, int y, int Object_ID)
{
	MAP_CHIP_ID Ob_ID = (MAP_CHIP_ID)Object_ID;
	int i = 0; int n = 0;
	for (bool loop_flg = true; loop_flg;)
	{
		bool y_flg = true; bool x_flg = true;
		if (g_Map[y][x + n + 1] == MAP_CHIP_ID::ENEMY_AREA)
		{
			g_map_flg[y][x + ++n] = false;
			y_flg = false;
		}
		if (g_Map[y][x + i - 1] == MAP_CHIP_ID::ENEMY_AREA)
		{
			g_map_flg[y][x + --i] = false;
			x_flg = false;
		}
		if (y_flg && x_flg)
			loop_flg = false;
	}
	vivid::Vector2 e_pos = { (float)(x * g_map_chip_size),(float)(y * g_map_chip_size) };
	float Rw = (x + n) * g_map_chip_size;
	float Lw = (x + i) * g_map_chip_size;
	if (Ob_ID==MAP_CHIP_ID::L_ENEMY)
		EnemyManager::GetInstance().GenerateEnemy(e_pos, Lw, Rw,-1);
	else
		EnemyManager::GetInstance().GenerateEnemy(e_pos, Lw, Rw, 1);
}
