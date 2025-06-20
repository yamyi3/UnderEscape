#pragma once
#include<list>
#include "vivid.h"
#include"wall/wall.h"

class WallManager
{
public:
	//�C���X�^���X�̎擾
	static WallManager& GetInstance();
	// ������
	void Initialize();
	// �X�V
	void Update();
	// �`��
	void Draw();
	// �J��
	void Finalize();

	bool CheckHitPlayer(const vivid::Vector2& center_pos, int height, int width);

	void GenerateWall(vivid::Vector2 pos, float V, float H);
	void GenerateWall(vivid::Vector2 pos1, vivid::Vector2 pos2);
	void GenerateWall(vivid::Vector2 pos, float V, float H,int color);
	void GenerateWall(vivid::Vector2 pos1, vivid::Vector2 pos2,int color);
	void Input_scroll(float s) { scroll = s; }
private:
	using WALL_LIST = std::list<Wall*>;
	WALL_LIST m_Wall;
	float scroll;

	WallManager();
	~WallManager() = default;
	WallManager(const WallManager& rhs) = delete;
	WallManager& operator=(const WallManager& rhs) = delete;
};
