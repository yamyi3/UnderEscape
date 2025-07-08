#pragma once
#include "vivid.h"

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
	//ステージのスクロール処理
	void ScrollStage(void);
	//地面座標のスタート地点取得
	vivid::Vector2 GetStartpos(void)
	{
		return vivid::Vector2(0.0f, 0.0f);
	}
	//地面のゴール地点の座標取得
	vivid::Vector2 GetGoalpos(void)
	{
		return vivid::Vector2((Stage::max_round * Stage::round_width), 0.0f);
	}
	//障害物座標の取得
	vivid::Vector2 GetWallpos(void)
	{
		return wall_pos;
	}
	//障害物の幅の取得
	float GetWallWidth(void)
	{
		return wall_width;
	}
	//障害物の高さの取得
	float GetWallHeight(void)
	{
		return wall_height;
	}
	//地面の高さの取得
	 float GetRoundHeight()
	{
		return round_pos->y;
	}
	float GetRoundHeight(vivid::Vector2 pos, float width, float height);
	float GetRWall(vivid::Vector2 pos, float width, float height);
	float GetLWall(vivid::Vector2 pos, float width, float height);
	float GetCeiling(vivid::Vector2 pos, float width, float height);

	void GenerateObject(int x, int y, int Object_ID);

	void GenerateEnemy(int x, int y, int Object_ID);

private:
	//地面の座標
	vivid::Vector2 round_pos[3];

	//ステージの始点の座標
	static vivid::Vector2	start_pos;

	//ステージの終点の座標
	static vivid::Vector2	goal_pos;

	//遮蔽物の座標
	vivid::Vector2 wall_pos;
	//遮蔽物の幅
	static const float wall_width;
	//遮蔽物の高さ
	static const float wall_height;
	//遮蔽物の色
	static unsigned int wall_color;

	//地面1枚の幅
	static const float	round_width;
	//地面の画像の枚数
	int		max_round;
	//スクロールの速度
	float	sc_speed;
	//自機の通常速度
	static const float	walk_speed;
	//自機のダッシュ速度
	static const float	dash_speed;
	//自機のしゃがみ速度
	static const float	sneak_speed;

	//シングルトンパターンの設定
	Stage(void) = default;
	~Stage(void) = default;
	Stage(const Stage& rhs) = default;
	Stage& operator = (const Stage& rhs) = default;

	bool cflg = 0;




	static const int g_map_chip_size;
	static const int g_map_chip_count_width=40;
	static const int g_map_chip_count_height=13;
	// マップチップ番号を列挙型で定義 
	enum class MAP_CHIP_ID
	{
		EMPTY,
		GROUND,
		BLOCK,
		WALL,
		ENEMY_AREA,
		R_ENEMY,
		L_ENEMY,
		START,
		GOAL,
	};

	// 配置データを入れておくための二次元配列(整数) 
	MAP_CHIP_ID g_Map[g_map_chip_count_height][g_map_chip_count_width] = { MAP_CHIP_ID::EMPTY };
	bool g_map_flg[g_map_chip_count_height][g_map_chip_count_width];
	bool g_map_terrain[g_map_chip_count_height][g_map_chip_count_width];
};