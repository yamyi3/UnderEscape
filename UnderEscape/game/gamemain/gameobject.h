#pragma once
#include "vivid.h"
//アイテムオブジェクトの状態
enum class ITEM_STATE
{
	DUMMY,		//ダミー
	PLACE,		//設置
	GET,		//プレイヤー取得
	THROW,		//投げられている
	BREAK,		//破壊
};

class Gameobject
{
public:
	Gameobject(void);
	~Gameobject(void) = default;

	//初期化
	void Initialize(vivid::Vector2);
	//更新
	void Update(vivid::Vector2, bool, float, float, bool, vivid::Vector2, bool);
	//描画
	void Draw(void);
	//解放
	void Finalize(void);
	//壊れる時の処理
	void BreakMove(void);
	//プレイヤーが持っている状態の処理
	void GetMove(vivid::Vector2, float, float);
	//プレイヤーが投げた後の処理
	void ThrowMove(vivid::Vector2);
	//プレイヤーが置いた後の処理
	void PutMove(vivid::Vector2);
	//プレイヤーが投げた後の処理(マウス）
	void ThrowMove3(vivid::Vector2, vivid::Vector2);

	//アイテムオブジェクトの座標取得
	vivid::Vector2 getItemPos(void)
	{
		return iPos;
	}
	//アイテムオブジェクトの中心点の取得
	vivid::Vector2 GetItemCenter(void)
	{
		return iCenter;
	}
	//アイテムオブジェクトの幅取得
	float GetItemWidth(void)
	{
		return item_width;
	}
	//アイテムオブジェクトの高さ取得
	float GetItemHeight(void)
	{
		return item_height;
	}

private:
	float Xspeed = 100.0f;				//飛距離のマイナス倍率(X軸)値を小さくすると飛距離が伸びる
	float Yspeed = 20.0f;				//飛距離のマイナス倍率(Y軸)値を小さくすると飛距離が伸びる
	vivid::Vector2 Mouse;				//自キャラからのマウスの座標
	vivid::Vector2 iPos;				//アイテムオブジェクトの座標
	vivid::Vector2 iCenter;				//アイテムオブジェクトの中心点
	bool catchFlg;						//取得の判断フラグ
	bool breakFlg;						//アイテムオブジェクトの破壊の判断フラグ
	bool itemFlg;						//着地の判定
	const float item_height = 32.0f;	//アイテムオブジェクトの高さ
	const float item_width = 32.0f;		//アイテムオブジェクトの幅
	const float throw_speed = 8.0f;		//アイテムオブジェクトの投げる速度
	float item_fall;					//アイテムオブジェクトの落下速度
	unsigned int iColor;				//アイテムオブジェクトの色

	float Ga = 1.0;						//重力加速度
	float V = 0.0;						//上昇する初速

	ITEM_STATE item_state = ITEM_STATE::PLACE;	//アイテムオブジェクトの状態(初期状態はPLACE(設置))
};