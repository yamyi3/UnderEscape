#pragma once
#include "vivid.h"
#include "enemy_status_id.h"

class Enemy
{
public:
	Enemy(void);
	~Enemy(void) = default;

	//初期化
	void Initialize(vivid::Vector2 pos, float L, float R, float vector, float ground);
	void Initialize(vivid::Vector2 pos, float L, float R, float vector);
	void Initialize(vivid::Vector2 pos, float L, float R);
	void Initialize(vivid::Vector2 pos);
	void Initialize(void);
	//更新
	void Update(void);
	//描画
	void Draw(void);

	void Finalize(void);
	//エネミーのポジションを出力
	vivid::Vector2 GetEnemyPos(void);
	//視界の半径を出力
	float GetCircleRadius(void);
	//視界の中心を出力
	vivid::Vector2	GetCircleCenterPos(void);
	//プレイヤーとの当たり判定をチェック
	bool CheckHitPlayer(const vivid::Vector2& center_c_pos, int c_height, int c_width);

	bool IsActive(void)const { return m_ActiveFlag; }
	void Destroy(void) { m_ActiveFlag = false; }

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
	static const int e_visibility_width_size;		//視界の横の大きさ
	static const int e_visibility_height_size;		//視界の縦の大きさ


	static const int e_width_size;					//エネミーの横のドット数
	static const int e_height_size;                 //エネミーの縦のドット数

	static const int mark_width_size;		//!の横のドット数
	static const int mark_height_size;		//!の縦のドット数

	static const float eSpeed;						//エネミーの巡回中の移動速度
	static const float eChaseSpeed;					//エネミーのプレイヤー追跡中の移動速度
	static const int Source_End_Range;				//警戒座標とのｘ軸の差がこの数値より短くなったら追跡を終了する。
	static const int Vigilance_time;				//追跡目標地点到達後の待機フレーム数

	static const int Surprised_time;				//追跡開始前の停止フレーム数
	static const float enemy_jump_height;			//ジャンプの高さ
	static const float enemy_jump_upspeed;			//ジャンプの上昇スピード
	static const float enemy_jump_downspeed;		//落下スピード(上昇スピードの何％か)
	static const int enemy_jump_power;				//ジャンプする際に参照する値(基本180)

	static const float		eCircleRadius;

	vivid::Vector2 ePos;				//エネミーの描画に使用するポジション
	vivid::Rect eRect;						//エネミーの画像範囲
	vivid::Vector2 eAnchor;		//エネミーのアンカー
	vivid::Vector2 eScale;				//エネミーのスケール


	vivid::Vector2 markPos;				//!の描画に使用するポジション
	vivid::Rect markRect;				//!の画像範囲
	vivid::Vector2 markAnchor;		//!のアンカー
	vivid::Vector2 markScale;				//!のスケール

	float Rwool;										//エネミー巡回中の右側の最大行動範囲用変数
	float Lwool;										//エネミー巡回中の左側の最大行動範囲用変数

	int gravity;									//ジャンプ、重力用の変数
	bool jpflg;											//ジャンプの可否の判定用
	float eGround;								//地面の高さ
	int eVector;									//エネミーの向いてる向き用
	vivid::Vector2 ChasePos;							//追跡目標地点;
	int Vigilance_Timer;							//追跡目標地点到達後の待機時間用
	int Surprised_Timer;							//追跡開始前の停止時間用


	bool m_ActiveFlag;	//アクティブフラグ

	vivid::Vector2	eCircleCenterPos;				//エネミーの視界の中心座標

	eSTATUS eStatus;				//エネミーの状態保存用
};