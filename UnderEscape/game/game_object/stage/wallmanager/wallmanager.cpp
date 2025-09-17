#include "wallmanager.h"


WallManager::WallManager()
	:scroll(0.0f, 0.0f)
{

}

WallManager& WallManager::GetInstance()
{
	static  WallManager instance;
	// TODO: return ステートメントをここに挿入します
	return instance;
}

void WallManager::Initialize()
{
}

void WallManager::Update()
{
	WALL_LIST::iterator it = m_Wall.begin();
	WALL_LIST::iterator end = m_Wall.end();
	while (it != end)
	{
		if (!(*it)->IsActive())
		{
			(*it)->Finalize();
			delete(*it);
			it = m_Wall.erase(it);
			continue;
		}
		(*it)->Update();
		++it;
	}
}

void WallManager::Draw()
{
	WALL_LIST::iterator it = m_Wall.begin();
	WALL_LIST::iterator end = m_Wall.end();
	while (it != end)
	{
		(*it)->Draw(scroll);

		++it;
	}
}

void WallManager::Finalize()
{
	WALL_LIST::iterator it = m_Wall.begin();
	WALL_LIST::iterator end = m_Wall.end();
	while (it != end)
	{
		(*it)->Finalize();

		delete(*it);

		++it;
	}
	m_Wall.clear();
}

bool WallManager::CheckHitPlayer(const vivid::Vector2& center_pos, int height, int width)
{
	WALL_LIST::iterator it = m_Wall.begin();
	WALL_LIST::iterator end = m_Wall.end();
	while (it != end)
	{
		Wall* wall = (*it);

		if ((*it)->CheckHitPlayer(center_pos, height, width))
			return true;
		++it;
	}
	return false;
}

void WallManager::GenerateWall(vivid::Vector2 pos, float V, float H)
{
	Wall* wall = nullptr;
	wall = new Wall();
	if (!wall)return;
	wall->Initialize(pos, V, H);

	m_Wall.push_back(wall);
}

void WallManager::GenerateWall(vivid::Vector2 pos1, vivid::Vector2 pos2)
{
	Wall* wall = nullptr;
	wall = new Wall();
	if (!wall)return;
	wall->Initialize(pos1, pos2);

	m_Wall.push_back(wall);
}

void WallManager::GenerateWall(vivid::Vector2 pos, float V, float H, int color)
{
	Wall* wall = nullptr;
	wall = new Wall();
	if (!wall)return;
	wall->Initialize(pos, V, H, color);

	m_Wall.push_back(wall);
}

void WallManager::GenerateWall(vivid::Vector2 pos1, vivid::Vector2 pos2, int color)
{
	Wall* wall = nullptr;
	wall = new Wall();
	if (!wall)return;
	wall->Initialize(pos1, pos2, color);

	m_Wall.push_back(wall);
}
