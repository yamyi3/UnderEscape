#pragma once
#include "vivid.h"
#include "..\item_id.h"
#include "../item.h"


class SoundItem : public Item
{
public:
	SoundItem();
	~SoundItem();
	//初期化
	void Initialize(vivid::Vector2 position);
	//描画
	void Draw(void);
	//プレイヤーが持っている状態の処理
	void GetMove(vivid::Vector2, float, float);
	//プレイヤーが投げた後の処理(マウス）
	void UseMove(float, vivid::Vector2);


private:
	float Xspeed ;						//飛距離のマイナス倍率(X軸)値を小さくすると飛距離が伸びる
	float Yspeed	;					//飛距離のマイナス倍率(Y軸)値を小さくすると飛距離が伸びる
	vivid::Vector2 Mouse;				//自キャラからのマウスの座標
	
	static const float item_height;		//アイテムオブジェクトの高さ
	static const float item_width;		//アイテムオブジェクトの幅
	static const float item_radius;		//アイテムオブジェクトの幅

};

