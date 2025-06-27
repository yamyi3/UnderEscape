#include "groundmanager.h"


GroundManager::GroundManager()
	:scroll(0.0f)
{

}

GroundManager& GroundManager::GetInstance()
{
	static  GroundManager instance;
	// TODO: return ステートメントをここに挿入します
	return instance;
}

void GroundManager::Initialize()
{
}

void GroundManager::Update()
{
	GROUND_LIST::iterator it = m_Ground.begin();
	GROUND_LIST::iterator end = m_Ground.end();
	while (it != end)
	{
		if (!(*it)->IsActive())
		{
			(*it)->Finalize();
			delete(*it);
			it = m_Ground.erase(it);
			continue;
		}
		(*it)->Update();
		++it;
	}
}

void GroundManager::Draw()
{
	GROUND_LIST::iterator it = m_Ground.begin();
	GROUND_LIST::iterator end = m_Ground.end();
	while (it != end)
	{
		(*it)->Draw(scroll);

		++it;
	}
}

void GroundManager::Finalize()
{
	GROUND_LIST::iterator it = m_Ground.begin();
	GROUND_LIST::iterator end = m_Ground.end();
	while (it != end)
	{
		(*it)->Finalize();

		delete(*it);

		++it;
	}
	m_Ground.clear();
}

bool GroundManager::CheckHitPlayer(const vivid::Vector2& center_pos, int height, int width)
{
	GROUND_LIST::iterator it = m_Ground.begin();
	GROUND_LIST::iterator end = m_Ground.end();
	while (it != end)
	{
		Ground* ground = (*it);

		if ((*it)->CheckHitPlayer(center_pos, height, width))
			return true;
		++it;
	}
	return false;
}

void GroundManager::GenerateGround(vivid::Vector2 pos, float V, float H)
{
	Ground* ground = nullptr;
	ground = new Ground();
	if (!ground)return;
	ground->Initialize(pos, V, H);

	m_Ground.push_back(ground);
}

void GroundManager::GenerateGround(vivid::Vector2 pos1, vivid::Vector2 pos2)
{
	Ground* ground = nullptr;
	ground = new Ground();
	if (!ground)return;
	ground->Initialize(pos1, pos2);

	m_Ground.push_back(ground);
}

void GroundManager::GenerateGround(vivid::Vector2 pos, float V, float H, int color)
{
	Ground* ground = nullptr;
	ground = new Ground();
	if (!ground)return;
	ground->Initialize(pos, V, H, color);

	m_Ground.push_back(ground);
}

void GroundManager::GenerateGround(vivid::Vector2 pos1, vivid::Vector2 pos2, int color)
{
	Ground* ground = nullptr;
	ground = new Ground();
	if (!ground)return;
	ground->Initialize(pos1, pos2, color);

	m_Ground.push_back(ground);
}
