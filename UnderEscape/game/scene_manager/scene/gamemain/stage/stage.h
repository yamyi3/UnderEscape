#pragma once
#include "vivid.h"
#include <iostream>
#include <vector>
#include "teleportmanager/teleportmanager.h"

class Stage
{
public:
	//インスタンスを生成、取得
	static Stage& GetInstance(void);
	//初期化
	void Initialize(void);
	//更新
	void Update(void);
	//描画
	void Draw(void);
	//解放
	void Finalize(void);
	//
	void MapSizeInitialize(void);
	//テレポート階段の判定取得
	bool GetStairsFlg(vivid::Vector2 cpos) { return TeleportManager::GetInstance().GetTeleportFlg(cpos); }
	//テレポート階段の座標取得
	vivid::Vector2 GetStairs(vivid::Vector2 cpos) { return TeleportManager::GetInstance().StairsTeleport(cpos); }
	//地面座標のスタート地点取得
	vivid::Vector2 GetStartpos(void)
	{
		return vivid::Vector2(0.0f, 0.0f);
	}
	//地面のゴール地点の座標取得
	vivid::Vector2 GetGoalpos(void)
	{
		return goal_pos;
	}

	//地面の高さの取得

	float GetRoundHeight(vivid::Vector2 pos, float width, float height, vivid::Vector2 anchor);
	float GetRWall(vivid::Vector2 pos, float width, float height, vivid::Vector2 anchor);
	float GetLWall(vivid::Vector2 pos, float width, float height, vivid::Vector2 anchor);
	float GetCeiling(vivid::Vector2 pos, float width, float height, vivid::Vector2 anchor);

	float GetRoundHeight(vivid::Vector2 pos, float width, float height);
	float GetRWall(vivid::Vector2 pos, float width, float height);
	float GetLWall(vivid::Vector2 pos, float width, float height);
	float GetCeiling(vivid::Vector2 pos, float width, float height);

	bool CheckHitWallPlayer(const vivid::Vector2& pos, int height, int width);

	void GenerateObject(int x, int y, int Object_ID);


	int GetStageWidthSize() { return g_map_chip_count_width * g_map_chip_size; }
	int GetStageHeightSize() { return g_map_chip_count_height * g_map_chip_size; }

	int GetStageWidthCount() { return g_map_chip_count_width; }
	int GetStageHeightCount() { return g_map_chip_count_height; }


	int GetMapChipSize(){ return g_map_chip_size; }
private:


	//ステージの始点の座標
	static vivid::Vector2	start_pos;

	//ステージの終点の座標
	static vivid::Vector2	goal_pos;

	//シングルトンパターンの設定
	Stage(void) = default;
	~Stage(void) = default;
	Stage(const Stage& rhs) = default;
	Stage& operator = (const Stage& rhs) = default;

	bool cflg = 0;




	static const int g_map_chip_size;
	int g_map_chip_count_width;
	int g_map_chip_count_height;
	// マップチップ番号を列挙型で定義 
	enum class MAP_CHIP_ID
	{
		EMPTY,			//0
		BLOCK,			//1
		WALL,			//2
		TPSTAIRS,		//3
		START,			//4
		GOAL,			//5
	};

	//配置データを入れておくための二次元配列(整数) 
	std::vector<std::vector<MAP_CHIP_ID>> g_Map;
	std::vector<std::vector<bool>> g_map_flg;
	std::vector<std::vector<bool>> g_map_terrain;
	std::vector<std::vector<bool>> g_map_wall;

	//MAP_CHIP_ID *g_Map;
	//bool *g_map_flg;
	//bool *g_map_terrain;
	//bool *g_map_wall;
};