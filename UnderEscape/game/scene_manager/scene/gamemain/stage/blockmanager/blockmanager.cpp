#include "blockmanager.h"


BlockManager::BlockManager()
	:scroll(0.0f)
{

}

BlockManager& BlockManager::GetInstance()
{
	static  BlockManager instance;
	// TODO: return ステートメントをここに挿入します
	return instance;
}

void BlockManager::Initialize()
{
}

void BlockManager::Update()
{
	BLOCK_LIST::iterator it = m_Block.begin();
	BLOCK_LIST::iterator end = m_Block.end();
	while (it != end)
	{
		if (!(*it)->IsActive())
		{
			(*it)->Finalize();
			delete(*it);
			it = m_Block.erase(it);
			continue;
		}
		(*it)->Update();
		++it;
	}
}

void BlockManager::Draw()
{
	BLOCK_LIST::iterator it = m_Block.begin();
	BLOCK_LIST::iterator end = m_Block.end();
	while (it != end)
	{
		(*it)->Draw(scroll);

		++it;
	}
}

void BlockManager::Finalize()
{
	BLOCK_LIST::iterator it = m_Block.begin();
	BLOCK_LIST::iterator end = m_Block.end();
	while (it != end)
	{
		(*it)->Finalize();

		delete(*it);

		++it;
	}
	m_Block.clear();
}

bool BlockManager::CheckHitPlayer(const vivid::Vector2& center_pos, int height, int width)
{
	BLOCK_LIST::iterator it = m_Block.begin();
	BLOCK_LIST::iterator end = m_Block.end();
	while (it != end)
	{
		Block* block = (*it);

		if ((*it)->CheckHitPlayer(center_pos, height, width))
			return true;
		++it;
	}
	return false;
}

void BlockManager::GenerateBlock(vivid::Vector2 pos, float V, float H)
{
	Block* block = nullptr;
	block = new Block();
	if (!block)return;
	block->Initialize(pos, V, H);

	m_Block.push_back(block);
}

void BlockManager::GenerateBlock(vivid::Vector2 pos1, vivid::Vector2 pos2)
{
	Block* block = nullptr;
	block = new Block();
	if (!block)return;
	block->Initialize(pos1, pos2);

	m_Block.push_back(block);
}

void BlockManager::GenerateBlock(vivid::Vector2 pos, float V, float H, int color)
{
	Block* block = nullptr;
	block = new Block();
	if (!block)return;
	block->Initialize(pos, V, H, color);

	m_Block.push_back(block);
}

void BlockManager::GenerateBlock(vivid::Vector2 pos1, vivid::Vector2 pos2, int color)
{
	Block* block = nullptr;
	block = new Block();
	if (!block)return;
	block->Initialize(pos1, pos2, color);

	m_Block.push_back(block);
}
