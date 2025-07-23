//character.h
#pragma once
#include "vivid.h"

enum class CHARA_STATE
{
	WAIT,
	WALK,
	RUN,
	SNEAKWAIT,
	SNEAKWALK,
	JUMP,

	MAX,
};

enum class CHARA_SKILL
{
	ANIMALLEG,
	INVISIBLE,

	MAX,
};

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

	//ステージとの当たり判定処理
	void StageHit();
	void HStageHit();
	void VStageHit();
	//画面端から出ないようにする処理
	void CheckWindow(void);
	//自機の操作処理
	void Control(void);
	//地面をすり抜けないようにする処理
	void RoundHit(float);
	//障害物(壁)に完全に隠れている時の処理
	bool CheckWallHit(vivid::Vector2, float, float);
	//敵の視界に入っていないかの判断
	bool CheckEnemyHit(vivid::Vector2, float);
	//アイテムの取得判断
	bool CheckObtainItem(vivid::Vector2, vivid::Vector2, float, float);
	//壁や視界に当たった時の色の変更
	void CheckHit(vivid::Vector2, float, float, vivid::Vector2, float);
	void CheckHit(vivid::Vector2, float, float,bool);
	//投げた判定
	bool CheckThrow(void);
	//置いた判定
	bool checkPut(void);
	//アニメーションの更新
	void UpdateAnimation(void);
	//自機の移動速度ごとの状態の判別
	void CheckMoveState(void);
	//ダッシュ中のスタミナの処理
	void DashStamina(void);
	//スタミナの回復処理
	void RecoveryStamina(void);
	//スタミナが0になった後の処理
	void LimitStamina(void);
	//スキルの発動処理
	void SkillMove(void);
	//発動可能スキルの切り替え処理
	void ChangeSkill(void);
	//クールタイムの処理
	void CoolTime(void);

	//座標の取得
	vivid::Vector2 GetCharapos(void) { return cPos; }
	//自機の幅の取得
	float GetCharaWidth(void) { return ch_width; }
	//自機の高さの取得
	float GetCharaHeight(void) { return ch_height; }
	//自機のアイテム取得フラグの取得
	bool GetCatchFlg(void) { return cCatch; }
	//歩行速度の取得
	float GetSneak(void) { return sneak_speed; }
	//通常速度の取得
	float GetWalk(void) { return walk_speed; }
	//ダッシュ速度の取得
	float GetDash(void) { return dash_speed; }
	//遮蔽フラグの取得
	bool GetShilding(void) { return cShielding; }	//シールド状態の取得

	//スクロール変数更新用
	void Scroll_Update();
	//スクロールの値を返す変数
	vivid::Vector2 GetScroll() { return Scroll; }

private:

	//スクロール用の変数
	vivid::Vector2 Scroll;
	static const float scroll_width_space;
	static const float scroll_height_space;

	vivid::Vector2 m_Velocity;			//慣性を含む速度計算

	//->描画関係
	//->自機関係
	vivid::Vector2 cPos;							//自機の座標
	static const float ch_width;					//自機の幅
	static const float ch_height;					//自機の高さ
	static unsigned int color;						//自機の色
	int	c_anime_frame;								//アニメーションの更新
	int	c_anime_timer;								//アニメーションタイマー
	int	c_change_anime_timer;						//アニメーションの切り替え基準値
	int	c_change_anime_frame;						//各アニメーションの枚数
	std::string	c_image[(int)CHARA_STATE::MAX] =	//自機の画像
	{	"data\\自機\\前待機スプレッド.png",			//待機
		"data\\自機\\前歩きスプレッド.png",			//歩行
		"data\\自機\\前走りスプレッド.png",			//ダッシュ
		"data\\自機\\前しゃがみ待機スプレッド.png",	//しゃがみ待機
		"data\\自機\\前しゃがみ歩きスプレッド.png",	//しゃがみ歩き
		"data\\自機\\前ジャンプスプレッド.png" };	//ジャンプ
	vivid::Rect		c_rect;							//画像の描画範囲
	vivid::Vector2	c_anchor;						//自機の拡大基準点
	vivid::Vector2	c_scale;						//自機のスケール
	float			c_rotate;						//自機の回転角度
	//<-自機関係
	//->スタミナ関係
	vivid::Vector2	stamina_pos;					//スタミナの描画座標
	std::string c_dash_image[2] =		
		//スタミナの画像
	{	"data\\自機\\限界スタミナ.png",				//走れない状態のスタミナ
		"data\\自機\\通常スタミナ.png" };			//通常時のスタミナ

	static const int stamina_width;					//スタミナゲージの幅(1つあたり)
	static const int stamina_height;				//スタミナゲージの高さ
	vivid::Rect		stamina_rect;					//画像の描画範囲
	vivid::Vector2	stamina_anchor;					//スタミナの拡大基準点
	vivid::Vector2	stamina_scale;					//スタミナのスケール
	//<-スタミナ関係
	//<-描画関係

	//->自機の速度関係
	static float ch_speed;				//自機の移動速度(代入用の変数)
	static const float walk_speed;		//自機の歩行時の移動速度
	static const float dash_speed;		//自機のダッシュ時の移動速度
	static const float sneak_speed;		//自機のしゃがみ時の移動速度
	static const float fatigue_speed;	//自機の疲労時の移動速度(スタミナが0の時の移動速度)
	const float jump_speed = -20.0f;	//自機のジャンプの速度
	const float fall_speed = 0.7f;		//自機の落下速度(重力)
	const float m_friction = 0.8f;		//慣性を作る
	const float cut_speed = 0.1f;		//自機の移動を0にする基準
	vivid::Vector2 accelerator;
	//<-自機の速度関係
	// 
	//->スタミナ関係
	static const int	c_max_stamina;		//自機のスタミナの最大値
	static int			c_stamina_gauge;	//自機のスタミナのゲージ
	static int			c_stamina_count;	//スタミナの減少速度を図るカウンタ
	static int			c_limit_recovery;	//疲労状態のスタミナ回復開始までのカウンタ
	static bool			c_stamina_dash;		//ダッシュ可能か判別するフラグ
	static bool			c_stamina_fatigue;	//自機が疲労状態か判別するフラグ
	static int			c_stamina_recovery;	//スタミナの回復カウンタ
	//<-スタミナ関係

	//->スキル関係
	static const int	activation_time;	//スキルの発動後の効果時間
	bool				skill_active_flag;	//スキルのアクティブフラグ
	int					active_count;		//スキル発動中のカウンタ
	static const int	skill_cool_time;	//スキルのクールタイムの最大数
	int					cool_time_count;	//クールタイムのカウンタ
	bool				skill_cool_flag;	//クールタイム処理を呼び出すフラグ
	/*各アクティブフラグは使用スキルの選択に使う(スキルはボタンでの切り替え式にする)*/
	//<-スキル関係

	static bool m_LandingFlag;			//接地フラグ
	static bool cCatch;					//オブジェクトを所持しているか判別するフラグ
	static bool cAlive;					//生存フラグ
	bool cShielding;					//遮蔽に入っているか判定するフラグ
	CHARA_STATE chara_state;			//自機の状態
	CHARA_SKILL chara_skill;			//スキルの使用状態

	//->インスタンスの生成
	Character(void) = default;
	~Character(void) = default;
	Character(const Character& rhs) = default;
	Character& operator = (const Character& rhs) = default;
	//<-インスタンスの生成

};