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

private:
	//地面の座標
	vivid::Vector2 round_pos[3];

	//遮蔽物の座標
	vivid::Vector2 wall_pos;
	//遮蔽物の幅
	static const float wall_width;
	//遮蔽物の高さ
	static const float wall_height;
	//遮蔽物の色
	static unsigned int wall_color;

	//地面1枚の幅
	float	round_width;
	//地面の画像の枚数
	int		max_round;
	//スクロールの速度
	float	sc_speed;
	//自機の通常速度
	static const float	run_speed;
	//自機のダッシュ速度
	static const float	dash_speed;
	//自機の歩行速度
	static const float	walk_speed;

	//シングルトンパターンの設定
	Stage(void) = default;
	~Stage(void) = default;
	Stage(const Stage& rhs) = default;
	Stage& operator = (const Stage& rhs) = default;

};