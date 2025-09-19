#pragma once
#include "vivid.h"
#include "enemy_id.h"
#include "../../item_manager/item/item_id.h"
class Enemy
{
public:
	Enemy::Enemy(int w_size, int h_size, float speed, float chase_speed,float jump_height, float jump_upspeed, float jump_downspeed, float circle_radius ,bool viewing_angle,int stun);
	~Enemy(void) = default;

	virtual void Initialize(vivid::Vector2 pos, float L, float R, float vector, float ground);//初期化
	virtual void Initialize(vivid::Vector2 pos, float L, float R, float vector);//初期化
	virtual void Initialize(vivid::Vector2 pos, float L, float R);//初期化
	virtual void Initialize(vivid::Vector2 pos);//初期化
	virtual void Initialize(void);
	virtual void Update();
	virtual void Draw(vivid::Vector2 scroll);
	virtual void Finalize(void);

	vivid::Vector2 GetEnemyPos(void);

	float GetCircleRadius(void);

	vivid::Vector2	GetCircleCenterPos(void);

	bool CheckHitPlayer(const vivid::Vector2& center_c_pos, int c_height, int c_width ,bool shielding);
	bool CheckSearchPlayer(const vivid::Vector2& center_c_pos, int c_height, int c_width, bool shielding);

	bool IsActive(void)const { return m_ActiveFlag; }
	void Destroy(void) { m_ActiveFlag = false; }

	void input_player_pos(vivid::Vector2 p_pos) { ChasePos = p_pos; }
	void sound_sensor(vivid::Vector2 sound_source, float sound_size);	//音の判定
	bool e_wool_jump();					//壁に当たったらジャンプする判定

	void jump();				//ジャンプ
	vivid::Vector2 Gravity		//重力
	(vivid::Vector2 pos			//キャラクターポジション
		, float yuka			//地面の高さ
		, int CharacterVSize	//キャラの縦方向のサイズ
		, vivid::Vector2 anchor	//キャラの軸(設定していなかったら{ 0.0f,0.0f }を入力)
		, float height			//ジャンプの高さ(ドット単位)
		, float upspeed			//登りスピード
		, float downspeed		//下りスピード(登りスピードの何％かなので100推奨)
	);
	void player_check(bool shielding);	//敵の索敵範囲内に自キャラがいると追いかけられる

	void ItemCheck(ITEM_ID id, vivid::Vector2 pos, bool active, float effect_area);
protected:

	int e_width_size;					//エネミーの横のドット数
	int e_height_size;                 //エネミーの縦のドット数

	static const int mark_width_size;		//!の横のドット数
	static const int mark_height_size;		//!の縦のドット数

	float eSpeed;						//エネミーの巡回中の移動速度
	float eChaseSpeed;					//エネミーのプレイヤー追跡中の移動速度
	static const int Source_End_Range;				//警戒座標とのｘ軸の差がこの数値より短くなったら追跡を終了する。
	static const int Vigilance_time;				//追跡目標地点到達後の待機フレーム数

	static const int Surprised_time;				//追跡開始前の停止フレーム数
	float enemy_jump_height;			//ジャンプの高さ
	float enemy_jump_upspeed;			//ジャンプの上昇スピード
	float enemy_jump_downspeed;		//落下スピード(上昇スピードの何％か)

	float		eCircleRadius;			//視界範囲

	vivid::Vector2 ePos;				//エネミーの描画に使用するポジション
	vivid::Rect eRect;						//エネミーの画像範囲
	vivid::Vector2 eAnchor;		//エネミーのアンカー
	vivid::Vector2 eScale;				//エネミーのスケール


	vivid::Vector2 markPos;				//!の描画に使用するポジション
	vivid::Rect markRect;				//!の画像範囲
	vivid::Vector2 markAnchor;		//!のアンカー
	vivid::Vector2 markScale;				//!のスケール

	float Rwall;										//エネミー巡回中の右側の最大行動範囲用変数
	float Lwall;										//エネミー巡回中の左側の最大行動範囲用変数

	int gravity;									//ジャンプ、重力用の変数
	bool jpflg;											//ジャンプの可否の判定用
	float eGround;								//地面の高さ
	int eVector;									//エネミーの向いてる向き用
	vivid::Vector2 ChasePos;							//追跡目標地点;
	int Sight_Check_Timer;
	int Vigilance_Timer;							//追跡目標地点到達後の待機時間用
	int Surprised_Timer;							//追跡開始前の停止時間用

	int TurnAroundtimer;
	static const int turn_around_ct;

	bool WallTouchFlg;		//壁に触れたかの判定保存
	float WallTouchPosX;	//壁に触れた時の位置

	bool m_ActiveFlag;	//アクティブフラグ

	int stun_time;
	int StunTimer;	//スタン時間用

	/*
	エネミーの視野角用
	true	::前方のみ
	false	::全方位
	*/
	bool ViewingAngle;

	std::string enemy_sight = "data\\敵視界.png";

	int AnimationTimer;
	static const int animation_change_time;
	int AnimationFrame;
	int AnimationMaxFrame[(int)eSTATUS::MAX];

	bool item_area;				//アイテムの効果範囲内にいるかどうかのフラグ
	vivid::Vector2 item_pos;		//アイテムの座標

	vivid::Vector2	eCircleCenterPos;

	eSTATUS eStatus;				//エネミーの状態保存用
	eCHASE_STATUS eChaseStatus;		//エネミーの追跡情報の判別用
};