#pragma once
#include "vivid.h"
#include "..\item_id.h"
#include "../item.h"


class FlashItem : public Item
{
public:
	FlashItem();
	~FlashItem();
	//初期化
	void Initialize(vivid::Vector2 position);
	//描画
	void Draw(void);
	//プレイヤーが持っている状態の処理
	void GetMove(vivid::Vector2, float, float);
	//プレイヤーが投げた後の処理(マウス）
	void UseMove(vivid::Vector2);

	float GetEffectiveArea()
	{
		return m_Area;
	}

private:
	float Xspeed;						//飛距離のマイナス倍率(X軸)値を小さくすると飛距離が伸びる
	float Yspeed;						//飛距離のマイナス倍率(Y軸)値を小さくすると飛距離が伸びる
	vivid::Vector2 Mouse;				//自キャラからのマウスの座標
	bool Flash_State;					//閃光の状態

	static const float item_height;		//アイテムオブジェクトの高さ
	static const float item_width;		//アイテムオブジェクトの幅
	static const float item_radius;		//アイテムオブジェクトの幅	
	static const int	max_item_time;		//アイテムの効果時間	
	static const int	max_number_of_times;	//アイテムの使用回数
};

