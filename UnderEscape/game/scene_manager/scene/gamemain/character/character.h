//character.h
#pragma once
#include "vivid.h"

//自機クラス
class Character
{
public:
	//インスタンスの取得
	static Character& GetInstance(void);
	//初期化
	void Initialize(vivid::Vector2);
	//更新
	void Update(void);
	//描画
	void Draw(void);
	//解放
	void Finalize(void);

	//画面端から出ないようにする処理
	void CheckWindow(void);
	//自機の操作処理
	void Control(void);
	//地面をすり抜けないようにする処理
	void RoundHit(vivid::Vector2);
	//障害物(壁)に完全に隠れている時の処理
	bool CheckWallHit(vivid::Vector2, float, float);
	//敵の視界に入っていないかの判断
	bool CheckEnemyHit(vivid::Vector2, float);
	//アイテムの取得判断
	bool CheckObtainItem(vivid::Vector2, vivid::Vector2, float, float);
	//壁や視界に当たった時の色の変更
	void CheckHit(vivid::Vector2, float, float, vivid::Vector2, float);
	//投げた判定
	bool CheckThrow(void);
	//置いた判定
	bool checkPut(void);
	//ゲージの上昇処理
	void UpperGauge(void);
	//ゲージの下降処理
	void DownerGauge(void);

	//座標の取得
	vivid::Vector2 GetCharapos(void)
	{
		return cPos;
	}
	float GetCharaWidth(void)
	{
		return ch_width;
	}
	float GetCharaHeight(void)
	{
		return ch_height;
	}
	bool GetCatchFlg(void)
	{
		return cCatch;
	}

private:
	vivid::Vector2 cPos;				//自機の座標
	vivid::Vector2 m_Velocity;			//慣性を含む速度計算

	float ch_width = 125.0f;			//自機の幅
	float ch_height = 192.0f;			//自機の高さ
	static unsigned int color;				//自機の色

	static float ch_speed;				//自機の移動速度
	static const float run_speed;		//自機の通常移動速度
	static const float dash_speed;		//自機のダッシュ時の移動速度
	static const float walk_speed;		//自機の歩行時の移動速度
	const float jump_speed = -20.0f;	//自機のジャンプの速度
	const float fall_speed = 0.7f;		//自機の落下速度(重力)
	const float m_friction = 0.8f;		//慣性を作る
	const float cut_speed = 0.1f;		//自機の移動を0にする基準

	vivid::Rect gauge_rect;				//ゲージ画像の表示幅
	vivid::Vector2 gPos;				//ゲージの表示座標
	const int max_gauge = 10;			//自機の発見ゲージの最大量
	static int gauge;							//自機の現在の発見ゲージの量
	const int one_gauge_frame = 60;		//発見ゲージ1個分あたりの増加にかかるフレーム数
	static int gauge_count_frame;				//発見ゲージが溜まっている間のフレーム数カウンタ
	const int downer_frame = 180;		//発見ゲージが1減るまでにかかるフレーム数
	static int down_gauge_count;				//ゲージ減少のカウンタ

	static bool m_LandingFlag;			//接地フラグ
	static bool cCatch;					//オブジェクトを所持しているか判別するフラグ
	static bool cAlive;					//生存フラグ

	//インスタンスの生成
	Character(void) = default;
	~Character(void) = default;
	Character(const Character& rhs) = default;
	Character& operator = (const Character& rhs) = default;
};