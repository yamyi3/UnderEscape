#pragma once
#include<list>
#include "vivid.h"
#include"wall/wall.h"

class WallManager
{
public:
	//インスタンスの取得
	static WallManager& GetInstance();
	// 初期化
	void Initialize();
	// 更新
	void Update();
	// 描画
	void Draw();
	// 開放
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
