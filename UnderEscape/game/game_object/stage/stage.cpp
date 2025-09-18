#include "stage.h"
#include "stage_id.h"
#include "../character/character.h"
#include "../enemy_manager/enemy_manager.h"
#include "../item_manager/item_manager.h"
#include "blockmanager/blockmanager.h"
#include "wallmanager/wallmanager.h"
#include "teleportmanager/teleportmanager.h"
#include "visualmanager/visualmanager.h"
#include <sstream>
#include <fstream>





const int Stage::g_map_chip_size = 100;

Stage::Stage(void)
	
{}


Stage& Stage::GetInstance(void)
{
	static Stage	instance;
	return instance;
}

void Stage::Initialize(void)
{
	start_pos = { 0.0f, 0.0f };
	goal_pos = { 0.0f,0.0f };
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

// ファイル読み込み
	FILE* fp = nullptr;
	fopen_s(&fp, "data\\map.csv", "r");
	fseek(fp, 0, SEEK_END);
	int size = ftell(fp);
	fseek(fp, 0, SEEK_SET);

	char* buf = new char[size + 1];   // +1 は文字列終端用
	fread(buf, size, 1, fp);
	buf[size] = '\0';                 // 文字列終端を付与
	fclose(fp);

	// CSV解析
	std::string data(buf);
	delete[] buf;

	std::stringstream ss(data);
	int k = 0;
	int value;

	while (ss >> value) {
		// 配列に代入（2次元→1次元に直して格納）
		g_Map[k / g_map_chip_count_width][k % g_map_chip_count_width] =
			static_cast<MAP_CHIP_ID>(value);
		++k;

		// 区切り文字が来たら読み飛ばす
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
				case MAP_CHIP_ID::EMPTY:
					break;
				case MAP_CHIP_ID::BLOCK:
				case MAP_CHIP_ID::WALL:
					GenerateObject(x, y, (int)g_Map[y][x]);
					break;
				case MAP_CHIP_ID::TPSTAIRS:
					TPcount++;
					break;
				case MAP_CHIP_ID::S_ITEM:
					ItemManager::GetInstance().CreateItem({ (float)(x * g_map_chip_size),(float)(y * g_map_chip_size) }, ITEM_ID::SOUND_ITEM);
					break;
				case MAP_CHIP_ID::F_ITEM:
					ItemManager::GetInstance().CreateItem({ (float)(x * g_map_chip_size),(float)(y * g_map_chip_size) }, ITEM_ID::FLASH_ITEM);
					break;
				case MAP_CHIP_ID::START:
					start_pos = { (float)(x * g_map_chip_size),((y+1) * g_map_chip_size) - Character::GetInstance().GetCharaHeight()};
					break;
				case MAP_CHIP_ID::GOAL:
					goal_pos = { (float)(x * g_map_chip_size),((y + 1) * g_map_chip_size) - Character::GetInstance().GetCharaHeight() };
					break;
				default:

					break;
				}
			}
		}
	}

	TeleportManager::GetInstance().Initialize(TPcount);
	VisualManager::GetInstance().Initialize();
}

void Stage::Update(void)
{
}

void Stage::Draw(void)
{

	vivid::Vector2 scroll = Character::GetInstance().GetScroll();
	WallManager::GetInstance().Input_scroll(scroll);
	BlockManager::GetInstance().Input_scroll(scroll);
	TeleportManager::GetInstance().Input_scroll(scroll);
	VisualManager::GetInstance().Input_scroll(scroll);

	WallManager::GetInstance().Draw();
	BlockManager::GetInstance().Draw();
	TeleportManager::GetInstance().Draw();
	VisualManager::GetInstance().Draw();

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
	// ファイル読み込み
	FILE* fp = nullptr;
	fopen_s(&fp, "data\\map_size.csv", "r");
	fseek(fp, 0, SEEK_END);
	int size = ftell(fp);
	fseek(fp, 0, SEEK_SET);

	char* buf = new char[size + 1];   // +1 は文字列終端用
	fread(buf, size, 1, fp);
	buf[size] = '\0';                 // 文字列終端を付与
	fclose(fp);

	// CSV解析
	std::string data(buf);
	delete[] buf;

	std::stringstream ss(data);
	int k = 0;
	int value;
	int work[2] = {};


	while (ss >> value) {
		// 配列に代入（2次元→1次元に直して格納）
		work[k] = static_cast<int>(value);
		++k;

		// 区切り文字が来たら読み飛ばす
		if (ss.peek() == ',' || ss.peek() == '\n') {
			ss.ignore();
		}
	}

	g_map_chip_count_height = work[0]+1;
	g_map_chip_count_width = work[1];
}



float Stage::GetRoundHeight(vivid::Vector2 pos, float width, float height, vivid::Vector2 anchor)
{
	pos -= anchor;
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
	return RoundY * g_map_chip_size+anchor.y;
}

float Stage::GetRWall(vivid::Vector2 pos, float width, float height, vivid::Vector2 anchor)
{
	pos -= anchor;
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


	return RWallX * g_map_chip_size - 1 - anchor.x;
}

float Stage::GetLWall(vivid::Vector2 pos, float width, float height, vivid::Vector2 anchor)
{
	pos -= anchor;
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

	return (LWallX + 1) * g_map_chip_size + anchor.x;
}

float Stage::GetCeiling(vivid::Vector2 pos, float width, float height, vivid::Vector2 anchor)
{
	pos -= anchor;
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
	return (CeilingY + 1) * g_map_chip_size + anchor.y;
}

float Stage::GetRoundHeight(vivid::Vector2 pos, float width, float height)
{
	return GetRoundHeight(pos, width, height, { 0,0 });
}

float Stage::GetRWall(vivid::Vector2 pos, float width, float height)
{
	return GetRWall(pos, width, height, { 0,0 });
}

float Stage::GetLWall(vivid::Vector2 pos, float width, float height)
{
	return GetLWall(pos, width, height, { 0,0 });
}

float Stage::GetCeiling(vivid::Vector2 pos, float width, float height)
{
	return GetCeiling(pos, width, height, { 0,0 });
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
	
	vivid::Vector2 ob_pos = { (float)(x * g_map_chip_size),(float)(y * g_map_chip_size) };
	int y_size = g_map_chip_size;
	int x_size = g_map_chip_size;

	switch (Ob_ID)
	{
	case MAP_CHIP_ID::BLOCK:
		BlockManager::GetInstance().GenerateBlock(ob_pos, y_size, x_size);
		g_map_terrain[y][x] = true;
		g_map_wall[y][x] = true;
		break;
	case MAP_CHIP_ID::WALL:
		WallManager::GetInstance().GenerateWall(ob_pos, y_size, x_size,0xff555555);
		g_map_wall[y][x] = true;
		break;
	default:
		break;
	}
}

