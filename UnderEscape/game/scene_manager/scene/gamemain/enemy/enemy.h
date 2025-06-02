#pragma once
#include "vivid.h"
#include "enemy_status_id.h"

class Enemy
{
public:
	Enemy(void);
	~Enemy(void) = default;

	void Initialize(vivid::Vector2 pos, float L, float R, float vector, float ground);//初期化
	void Initialize(vivid::Vector2 pos, float L, float R, float vector);//初期化
	void Initialize(vivid::Vector2 pos, float L, float R);//初期化
	void Initialize(void);
	void Update(void);
	void Draw(void);
	void Finalize(void);

	vivid::Vector2 GetEnemyPos(void);

	float GetCircleRadius(void);

	vivid::Vector2	GetCircleCenterPos(void);

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

private:
	const int e_width_size = 64;						//エネミーの横のドット数
	const int e_height_size = 64;                       //エネミーの縦;;;;のドット数
	vivid::Vector2 ePos = { 0.0f,0.0f };				//エネミーの描画に使用するポジション
	vivid::Rect eRect = { 0,0,e_height_size,e_width_size };						//エネミーの画像範囲
	vivid::Vector2 eAnchor = { e_width_size / 2.0f,e_height_size / 2.0f };		//エネミーのアンカー
	vivid::Vector2 eScale = { 1.0f,1.0f };				//エネミーのスケール

	const int exclamation_width_size = 32;						//!の横のドット数
	const int exclamation_height_size = 32;                       //!の縦のドット数
	vivid::Vector2 exclamationPos = { 0.0f,0.0f };				//!の描画に使用するポジション
	vivid::Rect exclamationRect = { 0,0,exclamation_height_size,exclamation_width_size };						//!の画像範囲
	vivid::Vector2 exclamationAnchor = { exclamation_width_size / 2.0f,exclamation_height_size / 2.0f };		//!のアンカー
	vivid::Vector2 exclamationScale = { 1.0f,1.0f };				//!のスケール

	float Rwool;										//エネミー巡回中の右側の最大行動範囲用変数
	float Lwool;										//エネミー巡回中の左側の最大行動範囲用変数
	const float eSpeed = 4;								//エネミーの巡回中の移動速度
	const float eChaseSpeed = 6;						//エネミーのプレイヤー追跡中の移動速度
	const int Source_End_Range = 4;						//警戒座標とのｘ軸の差がこの数値より短くなったら追跡を終了する。
	int gravity = 0;										//ジャンプ、重力用の変数
	bool jpflg;											//ジャンプの可否の判定用
	float eGround = 600;									//地面の高さ
	int eVector = 1;									//エネミーの向いてる向き用
	vivid::Vector2 ChasePos;							//追跡目標地点;
	int Vigilance_Timer = 0;							//追跡目標地点到達後の待機時間用
	const int Vigilance_time = 150;						//追跡目標地点到達後の待機フレーム数
	int Surprised_Timer = 0;							//追跡開始前の停止時間用
	const int Surprised_time = 30;						//追跡開始前の停止フレーム数
	const float enemy_jump_height = 150;				//ジャンプの高さ
	const float enemy_jump_upspeed = 3;					//ジャンプの上昇スピード
	const float enemy_jump_downspeed = 100;				//落下スピード(上昇スピードの何％か)

	const float		eCircleRadius;
	vivid::Vector2	eCircleCenterPos;

	eSTATUS eStatus = eSTATUS::Wandering;				//エネミーの状態保存用
};