#include "enemy_manager.h"
#include "..\character\character.h"
#include "enemy/spider_robo/spider_robo.h"
#include "enemy/creature/creature.h"
#include "../stage/stage.h"
#include <sstream>
#include <fstream>

EnemyManager& EnemyManager::GetInstance()
{
	static  EnemyManager instance;
	// TODO: return ステートメントをここに挿入します
	return instance;
}

void EnemyManager::Initialize()
{
	scroll = { 0.0f,0.0f };

	const int g_map_chip_count_width = Stage::GetInstance().GetStageWidthCount();
	const int g_map_chip_count_height = Stage::GetInstance().GetStageHeightCount();
	EnemySheet.resize(g_map_chip_count_height, std::vector<ENEMY_SHEET_ID>(g_map_chip_count_width));
	for (int y = 0; y < g_map_chip_count_height; y++)
		for (int x = 0; x < g_map_chip_count_width; x++)
			EnemySheet[y][x] = ENEMY_SHEET_ID::SPACE;

	// ファイル読み込み
	FILE* fp = nullptr;
	fopen_s(&fp, "data\\enemy.csv", "r");
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
		EnemySheet[k / g_map_chip_count_width][k % g_map_chip_count_width] =
			static_cast<ENEMY_SHEET_ID>(value);
		++k;

		// 区切り文字が来たら読み飛ばす
		if (ss.peek() == ',' || ss.peek() == '\n') {
			ss.ignore();
		}
	}
	for (int y = 0; y < g_map_chip_count_height; y++)
		for (int x = 0; x < g_map_chip_count_width; x++)
			switch (EnemySheet[y][x])
			{
			case ENEMY_SHEET_ID::SPACE:break;
			case ENEMY_SHEET_ID::BLOCK:break;
			case ENEMY_SHEET_ID::R_SPIDER_ROBO:SheetGenerateEnemy(x, y, ENEMY_ID::SPIDER_ROBO,  1);break;
			case ENEMY_SHEET_ID::L_SPIDER_ROBO:SheetGenerateEnemy(x, y, ENEMY_ID::SPIDER_ROBO, -1);break;
			case ENEMY_SHEET_ID::R_CREATURE:SheetGenerateEnemy(x, y, ENEMY_ID::CREATURE,  1);break;
			case ENEMY_SHEET_ID::L_CREATURE:SheetGenerateEnemy(x, y, ENEMY_ID::CREATURE, -1);break;
			case ENEMY_SHEET_ID::ENEMY_ACT_AREA:break;
			default:break;
			}
}

void EnemyManager::Update()
{
	ENEMY_LIST::iterator it = m_Enemy.begin();
	ENEMY_LIST::iterator end = m_Enemy.end();

	while (it != end)
	{
		if (!(*it)->IsActive())
		{
			(*it)->Finalize();

			delete(*it);

			it = m_Enemy.erase(it);

			continue;
		}
		(*it)->Update();

		++it;
	}
}

void EnemyManager::Draw()
{
	scroll = Character::GetInstance().GetScroll();
	ENEMY_LIST::iterator it = m_Enemy.begin();
	ENEMY_LIST::iterator end = m_Enemy.end();

	while (it != end)
	{
		(*it)->Draw(scroll);

		++it;
	}
}

void EnemyManager::Finalize()
{
	ENEMY_LIST::iterator it = m_Enemy.begin();
	ENEMY_LIST::iterator end = m_Enemy.end();
	while (it != end)
	{
		(*it)->Finalize();

		delete(*it);

		++it;
	}
	m_Enemy.clear();
}

void EnemyManager::GenerateEnemy(ENEMY_ID enemy_id, vivid::Vector2 pos, float L, float R, float vector, float ground)
{
	Enemy* enemy = nullptr;
	switch (enemy_id)
	{
	case ENEMY_ID::SPIDER_ROBO:
		enemy = new SpiderRobo();
		break;
	case ENEMY_ID::CREATURE:
		enemy = new Creature();
		break;
	default:
		break;
	}
	if (!enemy)return;
	enemy->Initialize(pos, L, R, vector, ground);

	m_Enemy.push_back(enemy);
}

void EnemyManager::GenerateEnemy(ENEMY_ID enemy_id, vivid::Vector2 pos, float L, float R, float vector)
{
	GenerateEnemy(enemy_id, pos, L, R, vector, 60000.0f);
}

void EnemyManager::GenerateEnemy(ENEMY_ID enemy_id, vivid::Vector2 pos, float L, float R)
{
	GenerateEnemy(enemy_id, pos, L, R, 1, 60000.0f);
}

void EnemyManager::GenerateEnemy(ENEMY_ID enemy_id, vivid::Vector2 pos)
{
	GenerateEnemy(enemy_id, pos, pos.x, pos.x, 1, 60000.0f);
}

void EnemyManager::GenerateEnemy(ENEMY_ID enemy_id)
{
	GenerateEnemy(enemy_id, { 300.0f, 500.0f }, 300.0f, 60000.0f);
}

void EnemyManager::GenerateEnemy(vivid::Vector2 pos, float L, float R, float vector, float ground)
{
	Enemy* enemy = nullptr;
	//enemy = new SpiderRobo();
	enemy = new Creature();
	if (!enemy)return;
	enemy->Initialize(pos, L, R, vector, ground);

	m_Enemy.push_back(enemy);
}

void EnemyManager::GenerateEnemy(vivid::Vector2 pos, float L, float R, float vector)
{
	GenerateEnemy(pos, L, R, vector, 60000.0f);
}

void EnemyManager::GenerateEnemy(vivid::Vector2 pos, float L, float R)
{
	GenerateEnemy(pos, L, R, 1, 60000.0f);
}

void EnemyManager::GenerateEnemy(vivid::Vector2 pos)
{
	GenerateEnemy(pos, pos.x, pos.x, 1, 60000.0f);
}

void EnemyManager::GenerateEnemy()
{
	GenerateEnemy({ 300.0f, 500.0f }, 300.0f, 60000.0f);
}

void EnemyManager::SheetGenerateEnemy(int x, int y, ENEMY_ID enemy_id, float vector)
{
	int g_map_chip_size = Stage::GetInstance().GetMapChipSize();
	int i = 0; int n = 0;
	for (bool loop_flg = true; loop_flg;)
	{
		bool y_flg = true; bool x_flg = true;
		if (EnemySheet[y][x + n + 1] == ENEMY_SHEET_ID::ENEMY_ACT_AREA)
		{
			++n;
			y_flg = false;
		}
		if (EnemySheet[y][x + i - 1] == ENEMY_SHEET_ID::ENEMY_ACT_AREA)
		{
			--i;
			x_flg = false;
		}
		if (y_flg && x_flg)
			loop_flg = false;
	}
	vivid::Vector2 e_pos = { (float)(x * g_map_chip_size),(float)(y * g_map_chip_size) };
	float Rw = (x + n) * g_map_chip_size;
	float Lw = (x + i) * g_map_chip_size;
	GenerateEnemy(enemy_id, e_pos, Lw, Rw, vector);
}

bool EnemyManager::CheckHitPlayer(const vivid::Vector2& center_pos, int height, int width, bool shielding)
{
	bool HitPlayerFlg = false;
	bool invisible = Character::GetInstance().GetFound();

	ENEMY_LIST::iterator it = m_Enemy.begin();
	ENEMY_LIST::iterator end = m_Enemy.end();

	if (invisible)
	while (it != end)
	{
		Enemy* enemy = (*it);

		if ((*it)->CheckHitPlayer(center_pos, height, width, shielding))
		{
			HitPlayerFlg = true;
			(*it)->input_player_pos(center_pos);
			(*it)->player_check(shielding);
		}

		++it;
	}
	return HitPlayerFlg;
}

bool EnemyManager::CheckSearchPlayer(const vivid::Vector2& center_pos, int height, int width,bool shielding)
{
	bool HitPlayerFlg = false;

	ENEMY_LIST::iterator it = m_Enemy.begin();
	ENEMY_LIST::iterator end = m_Enemy.end();

	while (it != end)
	{
		Enemy* enemy = (*it);

		if ((*it)->CheckSearchPlayer(center_pos, height, width))
		{
			HitPlayerFlg = true;
			(*it)->input_player_pos(center_pos);
			(*it)->player_check(shielding);
		}

		++it;
	}
	return HitPlayerFlg;
}

void EnemyManager::sound_sensor(vivid::Vector2 sound_source, float sound_size)
{
	ENEMY_LIST::iterator it = m_Enemy.begin();
	ENEMY_LIST::iterator end = m_Enemy.end();

	while (it != end)
	{
		Enemy* enemy = (*it);

		(*it)->sound_sensor(sound_source, sound_size);

		++it;
	}
}