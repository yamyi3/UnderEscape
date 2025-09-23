#pragma once
#include "vivid.h"
#include "..\item_id.h"
#include "../item.h"


class CSoundItem : public CItem
{
public:
	CSoundItem(void);
	~CSoundItem(void);
	//初期化
	void Initialize(vivid::Vector2 position);
	//描画
	void Draw(void);
	//プレイヤーが持っている状態の処理
	void GetMove(vivid::Vector2, float, float);
	//プレイヤーが投げた後の処理(マウス）
	void UseMove();

	void SetOrbitPosition(vivid::Vector2 position, vivid::Vector2 c_pos);

private:
	std::string	SoundBom;
	float m_X_Speed;						//飛距離のマイナス倍率(X軸)値を小さくすると飛距離が伸びる
	float m_Y_Speed;						//飛距離のマイナス倍率(Y軸)値を小さくすると飛距離が伸びる
	vivid::Vector2 m_Mouse_Pos;				//自キャラからのマウスの座標
	vivid::Vector2 m_KeepVector;			//投擲時のスティックの方向を保存する

	static const float m_height;			//アイテムオブジェクトの高さ
	static const float m_width;				//アイテムオブジェクトの幅
	static const float m_radius;			//アイテムオブジェクトの幅	
	static const int	m_max_time;			//アイテムの効果時間	
	static const int	m_number_of_times;	//アイテムの効果時間	
	static const float m_effect_area;		//アイテム効果範囲


};

