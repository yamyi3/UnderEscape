#pragma once
#include<list>
#include "vivid.h"
#include"ground/ground.h"

class GroundManager
{
public:
	//インスタンスの取得
	static GroundManager& GetInstance();
	// 初期化
	void Initialize();
	// 更新
	void Update();
	// 描画
	void Draw();
	// 開放
	void Finalize();

	bool CheckHitPlayer(const vivid::Vector2& center_pos, int height, int width);

	void GenerateGround(vivid::Vector2 pos, float V, float H);
	void GenerateGround(vivid::Vector2 pos1, vivid::Vector2 pos2);
	void GenerateGround(vivid::Vector2 pos, float V, float H, int color);
	void GenerateGround(vivid::Vector2 pos1, vivid::Vector2 pos2, int color);
	void Input_scroll(float s) { scroll = s; }
private:
	using GROUND_LIST = std::list<Ground*>;
	GROUND_LIST m_Ground;
	float scroll;

	GroundManager();
	~GroundManager() = default;
	GroundManager(const GroundManager& rhs) = delete;
	GroundManager& operator=(const GroundManager& rhs) = delete;
};
