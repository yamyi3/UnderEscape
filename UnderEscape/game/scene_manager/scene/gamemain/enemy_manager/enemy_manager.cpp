#include "enemy_manager.h"
#include "..\character\character.h"
#include "enemy/spider_robo/spider_robo.h"

EnemyManager& EnemyManager::GetInstance()
{
	static  EnemyManager instance;
	// TODO: return ステートメントをここに挿入します
	return instance;
}

void EnemyManager::Initialize()
{
	scroll = { 0.0f,0.0f };
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

void EnemyManager::GenerateEnemy(vivid::Vector2 pos, float L, float R, float vector, float ground)
{
	Enemy* enemy = nullptr;
	enemy = new SpiderRobo();
	if (!enemy)return;
	enemy->Initialize(pos, L, R, vector, ground);

	m_Enemy.push_back(enemy);
}

void EnemyManager::GenerateEnemy(vivid::Vector2 pos, float L, float R, float vector)
{
	Enemy* enemy = nullptr;
	enemy = new SpiderRobo();
	if (!enemy)return;
	enemy->Initialize(pos, L, R, vector);

	m_Enemy.push_back(enemy);
}

void EnemyManager::GenerateEnemy(vivid::Vector2 pos, float L, float R)
{
	Enemy* enemy = nullptr;
	enemy = new SpiderRobo();
	if (!enemy)return;
	enemy->Initialize(pos, L, R);

	m_Enemy.push_back(enemy);
}

void EnemyManager::GenerateEnemy(vivid::Vector2 pos)
{
	Enemy* enemy = nullptr;
	enemy = new SpiderRobo();
	if (!enemy)return;
	enemy->Initialize(pos);

	m_Enemy.push_back(enemy);
}

void EnemyManager::GenerateEnemy()
{
	Enemy* enemy = nullptr;
	enemy = new SpiderRobo();
	if (!enemy)return;
	enemy->Initialize();

	m_Enemy.push_back(enemy);
}

bool EnemyManager::CheckHitPlayer(const vivid::Vector2& center_pos, int height, int width,bool shielding)
{
	bool HitPlayerFlg = false;

	ENEMY_LIST::iterator it = m_Enemy.begin();
	ENEMY_LIST::iterator end = m_Enemy.end();

	while (it != end)
	{
		Enemy* enemy = (*it);

		if ((*it)->CheckHitPlayer(center_pos, height, width))
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