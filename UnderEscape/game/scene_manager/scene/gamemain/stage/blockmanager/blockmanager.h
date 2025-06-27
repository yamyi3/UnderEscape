#pragma once
#include<list>
#include "vivid.h"
#include"block/block.h"

class BlockManager
{
public:
	//�C���X�^���X�̎擾
	static BlockManager& GetInstance();
	// ������
	void Initialize();
	// �X�V
	void Update();
	// �`��
	void Draw();
	// �J��
	void Finalize();

	bool CheckHitPlayer(const vivid::Vector2& center_pos, int height, int width);

	void GenerateBlock(vivid::Vector2 pos, float V, float H);
	void GenerateBlock(vivid::Vector2 pos1, vivid::Vector2 pos2);
	void GenerateBlock(vivid::Vector2 pos, float V, float H, int color);
	void GenerateBlock(vivid::Vector2 pos1, vivid::Vector2 pos2, int color);
	void Input_scroll(float s) { scroll = s; }
private:
	using BLOCK_LIST = std::list<Block*>;
	BLOCK_LIST m_Block;
	float scroll;

	BlockManager();
	~BlockManager() = default;
	BlockManager(const BlockManager& rhs) = delete;
	BlockManager& operator=(const BlockManager& rhs) = delete;
};
