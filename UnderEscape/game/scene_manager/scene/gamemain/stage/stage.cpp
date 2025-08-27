#include "stage.h"
#include "../character/character.h"
#include "../enemy_manager/enemy_manager.h"
#include "blockmanager/blockmanager.h"
#include "groundmanager/groundmanager.h"
#include "wallmanager/wallmanager.h"
#include "teleportmanager/teleportmanager.h"
#include <sstream>
#include <iostream>
#include <fstream>


vivid::Vector2 Stage::start_pos = { 0.0f, vivid::WINDOW_HEIGHT - 300.0f };
vivid::Vector2 Stage::goal_pos = { 0,0 };


const int Stage::g_map_chip_size = 100;
//const int Stage::g_map_chip_count_width = 40;
//const int Stage::g_map_chip_count_height = 26;

Stage& Stage::GetInstance(void)
{
	static Stage	instance;
	return instance;
}

void Stage::Initialize(void)
{
	//g_Map = new MAP_CHIP_ID[g_map_chip_count_height];
	//for (int i = 0; i < g_map_chip_count_height; i++)
	//{
	//	g_Map = new MAP_CHIP_ID[g_map_chip_count_width];
	//}
	MapSizeInitialize();
	g_Map.resize(g_map_chip_count_height, std::vector<MAP_CHIP_ID>(g_map_chip_count_width));
	g_map_flg.resize(g_map_chip_count_height, std::vector<bool>(g_map_chip_count_width));
	g_map_terrain.resize(g_map_chip_count_height, std::vector<bool>(g_map_chip_count_width));
	g_map_wall.resize(g_map_chip_count_height, std::vector<bool>(g_map_chip_count_width));

	for (int y = 0; y < g_map_chip_count_height; y++)
		for (int x = 0; x < g_map_chip_count_width; x++)
		{
			g_map_flg[y][x] = true;
			g_map_terrain[y][x] = false;
			g_map_wall[y][x] = false;
			g_Map[y][x] = MAP_CHIP_ID::EMPTY;
		}


	////�t�@�C������

	//FILE* fp = nullptr;
	//// �t�@�C�����J�� 
	//fopen_s(&fp, "data\\map.csv", "r");
	//// �T�C�Y�𒲂ׂ� 
	//fseek(fp, 0, SEEK_END);
	//int size = ftell(fp);
	//fseek(fp, 0, SEEK_SET);
	//// �T�C�Y���������ꕨ��p�ӂ���(�ꎞ�I�ȃf�[�^) 
	//char* buf = new char[size];
	//// �f�[�^(CSV�t�@�C�����̕�����)��ǂݍ��� 
	//fread(buf, size, 1, fp);
	//// �t�@�C�������
	//fclose(fp);

	////�f�[�^���

	//	// �f�[�^�̃T�C�Y���J��Ԃ� 
	//for (int i = 0, k = 0; i < size; ++i)
	//{
	//	// ������0�`11�ł���ΐ��l�ɕϊ����� 
	//	if (buf[i] >= '0' && buf[i] <= '11')
	//	{
	//		char t = buf[i];
	//		g_Map[k / g_map_chip_count_width][k % g_map_chip_count_width] =
	//			(MAP_CHIP_ID)atoi(&t);
	//		++k;
	//	}
	//}
	//// �ꎞ�I�ȃf�[�^���폜 
	//delete[] buf;
	
	



// �t�@�C���ǂݍ���
	FILE* fp = nullptr;
	fopen_s(&fp, "data\\map.csv", "r");
	fseek(fp, 0, SEEK_END);
	int size = ftell(fp);
	fseek(fp, 0, SEEK_SET);

	char* buf = new char[size + 1];   // +1 �͕�����I�[�p
	fread(buf, size, 1, fp);
	buf[size] = '\0';                 // ������I�[��t�^
	fclose(fp);

	// CSV���
	std::string data(buf);
	delete[] buf;

	std::stringstream ss(data);
	int k = 0;
	int value;

	while (ss >> value) {
		// �z��ɑ���i2������1�����ɒ����Ċi�[�j
		g_Map[k / g_map_chip_count_width][k % g_map_chip_count_width] =
			static_cast<MAP_CHIP_ID>(value);
		++k;

		// ��؂蕶����������ǂݔ�΂�
		if (ss.peek() == ',' || ss.peek() == '\n') {
			ss.ignore();
		}
	}

	
	int TPcount=0;

	for (int y = 0; y < g_map_chip_count_height; y++)
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
				case Stage::MAP_CHIP_ID::RSTAIRS:
					break;
				case Stage::MAP_CHIP_ID::LSTAIRS:
					break;
				case Stage::MAP_CHIP_ID::ENEMY_AREA:
					g_map_flg[y][x] = true;
					break;
				case Stage::MAP_CHIP_ID::R_ENEMY:
				case Stage::MAP_CHIP_ID::L_ENEMY:
					GenerateEnemy(x, y, (int)g_Map[y][x]);
				case Stage::MAP_CHIP_ID::TPSTAIRS:
					TPcount++;
					break;
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

	TeleportManager::GetInstance().Initialize(TPcount);

}

void Stage::Update(void)
{
}

void Stage::Draw(void)
{

	vivid::Vector2 scroll = Character::GetInstance().GetScroll();
	WallManager::GetInstance().Input_scroll(scroll);
	GroundManager::GetInstance().Input_scroll(scroll);
	BlockManager::GetInstance().Input_scroll(scroll);
	TeleportManager::GetInstance().Input_scroll(scroll);

	WallManager::GetInstance().Draw();
	GroundManager::GetInstance().Draw();
	BlockManager::GetInstance().Draw();
	TeleportManager::GetInstance().Draw();

	if (cflg)
	{
		vivid::DrawText(40, "zzzzzz", { 500,500 });
	}
}

void Stage::Finalize(void)
{
}

void Stage::MapSizeInitialize(void)
{
	// �t�@�C���ǂݍ���
	FILE* fp = nullptr;
	fopen_s(&fp, "data\\map_size.csv", "r");
	fseek(fp, 0, SEEK_END);
	int size = ftell(fp);
	fseek(fp, 0, SEEK_SET);

	char* buf = new char[size + 1];   // +1 �͕�����I�[�p
	fread(buf, size, 1, fp);
	buf[size] = '\0';                 // ������I�[��t�^
	fclose(fp);

	// CSV���
	std::string data(buf);
	delete[] buf;

	std::stringstream ss(data);
	int k = 0;
	int value;
	int work[2] = {};


	while (ss >> value) {
		// �z��ɑ���i2������1�����ɒ����Ċi�[�j
		work[k] = static_cast<int>(value);
		++k;

		// ��؂蕶����������ǂݔ�΂�
		if (ss.peek() == ',' || ss.peek() == '\n') {
			ss.ignore();
		}
	}

	g_map_chip_count_height = work[0];
	g_map_chip_count_width = work[1];
}

void Stage::ScrollStage(void)
{
	////keyboard�l�[���X�y�[�X�̐錾
	//namespace keyboard = vivid::keyboard;

	////�ʏ펞�̓X�N���[�����x���ʏ푬�x�ɂȂ�
	//sc_speed = walk_speed;
	////��SHIFT�������Ă���Ԃ̓X�N���[�����x���_�b�V�����x�ɂȂ�
	//if (keyboard::Button(keyboard::KEY_ID::LSHIFT))
	//{
	//	sc_speed = dash_speed;
	//}
	////��CTRL�������Ă���Ԃ̓X�N���[�����x�����s���x�ɂȂ�
	//if (keyboard::Button(keyboard::KEY_ID::LCONTROL))
	//{
	//	sc_speed = sneak_speed;
	//}

	////�������ւ̃X�N���[������
	//if (keyboard::Button(keyboard::KEY_ID::A))
	//{
	//	//�w�i�̃X�N���[���̏���
	//	for (int i = 0; i < max_round; i++)
	//	{
	//		round_pos[i].x = round_pos[i].x + sc_speed;
	//		if (round_pos[i].x > round_width)
	//		{
	//			round_pos[i].x = -round_width - (round_width - round_pos[i].x);
	//		}
	//	}
	//}
	////�E�����ւ̃X�N���[������
	//if (keyboard::Button(keyboard::KEY_ID::D))
	//{
	//	//�w�i�̉E�X�N���[������
	//	for (int i = 0; i < max_round; i++)
	//	{
	//		round_pos[i].x = round_pos[i].x - sc_speed;
	//		if (round_pos[i].x < -round_width) {
	//			round_pos[i].x = round_width - (-round_width - round_pos[i].x);
	//		}
	//	}
	//}
}

float Stage::GetRoundHeight(vivid::Vector2 pos, float width, float height)
{
	int WidthXNum = width / g_map_chip_size + 1;
	int Y = (pos.y + height) / g_map_chip_size;
	if (Y < 1)Y = 1;
	int RoundY = g_map_chip_count_height;
	int n = 0;
	do {
		float XPos = (pos.x + ((width / WidthXNum) * n));
		if (n == 0)XPos = pos.x + 10;
		if (n == WidthXNum)XPos = pos.x + width - 10;
		int X = XPos / g_map_chip_size;
		int WY = RoundY;
		for (int i = Y; i >= 0 && i < g_map_chip_count_height && g_map_terrain[i - 1][X] == false; i++)
			WY = i;
		if (RoundY > WY)
			RoundY = WY;
		n++;
	} while (n <= WidthXNum);
	return RoundY * g_map_chip_size;
}

float Stage::GetRWall(vivid::Vector2 pos, float width, float height)
{
	int HeightYNum = height / g_map_chip_size + 1;
	int RWallX = g_map_chip_count_width;
	int X = (pos.x + width) / g_map_chip_size;
	int n = 0;
	do {
		float YPos = (pos.y + ((height / HeightYNum) * n));
		if (n == 0)YPos = pos.y + 10;
		if (n == HeightYNum)YPos = pos.y + height - 10;
		int Y = YPos / g_map_chip_size;
		if (Y < 0)Y = 0;
		int WX = RWallX;
		for (int i = X; i >= 0 && i < g_map_chip_count_width && g_map_terrain[Y][i - 1] == false; i++)
			WX = i;
		if (RWallX > WX)
			RWallX = WX;
		n++;
	} while (n <= HeightYNum);


	return RWallX * g_map_chip_size - 1;
}

float Stage::GetLWall(vivid::Vector2 pos, float width, float height)
{
	int HeightYNum = height / g_map_chip_size + 1;
	int LWallX = 0;
	int X = (pos.x) / g_map_chip_size;
	int n = 0;
	do {
		float YPos = (pos.y + ((height / HeightYNum) * n));
		if (n == 0)YPos = pos.y + 10;
		if (n == HeightYNum)YPos = pos.y + height - 10;
		int Y = YPos / g_map_chip_size;
		if (Y < 0)Y = 0;
		int WX = LWallX;
		for (int i = X; i >= 0 && i < g_map_chip_count_width && g_map_terrain[Y][i + 1] == false; i--)
			WX = i;
		if (LWallX < WX)
			LWallX = WX;
		n++;
	} while (n <= HeightYNum);

	return (LWallX + 1) * g_map_chip_size;
}

float Stage::GetCeiling(vivid::Vector2 pos, float width, float height)
{
	int WidthXNum = width / g_map_chip_size + 1;
	int Y = (pos.y) / g_map_chip_size;
	int CeilingY = 0;
	int n = 0;
	do {
		float XPos = (pos.x + ((width / WidthXNum) * n));
		if (n == 0)XPos = pos.x + 10;
		if (n == WidthXNum)XPos = pos.x + width - 10;
		int X = XPos / g_map_chip_size;
		int WY = 0;
		for (int i = Y; i >= 0 && i < g_map_chip_count_height && g_map_terrain[i + 1][X] == false; i--)
			WY = i;
		if (CeilingY < WY)
			CeilingY = WY;
		n++;
	} while (n <= WidthXNum);
	return (CeilingY + 1) * g_map_chip_size;
}

bool Stage::CheckHitWallPlayer(const vivid::Vector2& pos, int height, int width)
{
	int Lx = pos.x / g_map_chip_size;
	int Rx = (pos.x + width) / g_map_chip_size;
	int TopY = pos.y / g_map_chip_size;
	int MiddleY = (pos.y + height) / g_map_chip_size;
	int BotomY = (pos.y + height) / g_map_chip_size;

	if (g_map_wall[TopY][Lx] && g_map_wall[MiddleY][Lx] && g_map_wall[BotomY][Lx] && g_map_wall[TopY][Rx] && g_map_wall[MiddleY][Rx] && g_map_wall[BotomY][Rx])
		return true;

	return false;
}

void Stage::GenerateObject(int x, int y, int Object_ID)
{
	MAP_CHIP_ID Ob_ID = (MAP_CHIP_ID)Object_ID;
	//int i = 1; int n = 1;
	//for (bool loop_flg = true; loop_flg;)
	//{
	//	bool y_flg = false; bool x_flg = false;
	//	for (int j = x; j <= x + n; j++)
	//		if (g_Map[y + i + 1][j] != Ob_ID && g_map_flg[y + i + 1][j] == false)
	//			y_flg = true;

	//	if (y_flg == false)
	//	{
	//		i++;
	//		for (int j = x; j <= x + n; j++)
	//		{
	//			if ((Ob_ID==MAP_CHIP_ID::GROUND||Ob_ID==MAP_CHIP_ID::BLOCK))
	//				g_map_terrain[y + i][j] = true;
	//			g_map_flg[y + i][j] = false;
	//		}
	//	}

	//	for (int j = x; j <= x + n; j++)
	//		if (g_Map[y + i][x + n + 1] != Ob_ID&& g_map_flg[j][x + n] == false)
	//			x_flg = true;

	//	if (x_flg == false)
	//	{
	//		n++;
	//		for (int j = y; j <= y+i; j++)
	//		{
	//			if (Ob_ID == MAP_CHIP_ID::GROUND || Ob_ID == MAP_CHIP_ID::BLOCK)
	//				g_map_terrain[j][x + n] = true;
	//			g_map_flg[j][x + n] = false;
	//		}
	//	}

	//	if ((y_flg && x_flg)||(((x+n)>=g_map_chip_count_width)||(y+i)>=g_map_chip_count_height)||n>=10||i>=10)
	//		loop_flg = false;
	//}
	//vivid::Vector2 ob_pos = { (float)(x * g_map_chip_size),(float)((y) * g_map_chip_size) };
	//int y_size = i * g_map_chip_size;
	//int x_size = n * g_map_chip_size;

	vivid::Vector2 ob_pos = { (float)(x * g_map_chip_size),(float)(y * g_map_chip_size) };
	int y_size = g_map_chip_size;
	int x_size = g_map_chip_size;

	switch (Ob_ID)
	{
	case Stage::MAP_CHIP_ID::GROUND:
		GroundManager::GetInstance().GenerateGround(ob_pos, y_size, x_size);
		g_map_terrain[y][x] = true;
		g_map_wall[y][x] = true;
		break;
	case Stage::MAP_CHIP_ID::BLOCK:
		BlockManager::GetInstance().GenerateBlock(ob_pos, y_size, x_size);
		g_map_terrain[y][x] = true;
		g_map_wall[y][x] = true;
		break;
	case Stage::MAP_CHIP_ID::WALL:
		WallManager::GetInstance().GenerateWall(ob_pos, y_size, x_size,0xff555555);
		g_map_wall[y][x] = true;
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
