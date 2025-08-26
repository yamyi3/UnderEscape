//character.cpp
#include "character.h"
#include "../stage/stage.h"

float	Character::ch_speed = sneak_speed;
unsigned Character::color = 0xffffffff;
bool	Character::m_LandingFlag = false;
bool	Character::cCatch = false;
bool	Character::cAlive = true;
CHARA_SKILL chara_skill = CHARA_SKILL::NORMAL;

const float Character::ch_width		 = 72.0f;			//自機の幅
const float Character::ch_height	 = 180.0f;			//自機の高さ
const float Character::walk_speed	 = 1.2f;			//自機の通常移動速度
const float Character::dash_speed	 = 2.4f;			//自機のダッシュ時の移動速度
const float Character::sneak_speed	 = 0.6f;			//自機の歩行時の移動速度
const float Character::fatigue_speed = 0.3f;			//自機の疲労時の移動速度

int			Character::skill_memory			= 1;
const int	Character::skill_cool_time		= 300;		//スキルのクールタイムの最大数(60フレーム換算5秒)
const int	Character::activation_time		= 300;		//スキルの効果時間(60フレーム換算5秒)
const int	Character::stamina_width		= 76;		//スタミナ現在の1つあたりの幅
const int	Character::stamina_height		= 16;		//スタミナゲージの高さ
const int	Character::c_max_stamina		= 5;		//自機のスタミナの最大値
int			Character::c_stamina_gauge		= 5;		//自機のスタミナのゲージ
int			Character::c_stamina_count		= 0;		//スタミナの減少速度を図るカウンタ
int			Character::c_limit_recovery		= 0;		//疲労状態のスタミナ回復までのカウンタ
int			Character::c_stamina_recovery	= 0;		//スタミナ回復のカウンタ
bool		Character::c_stamina_dash		= true;		//ダッシュ可能か判別するフラグ
bool		Character::c_stamina_fatigue	= false;	//自機が疲労状態か判別するフラグ
const int	Character::c_draw_stamina		= 60;		//スタミナの描画する最大秒数(60フレーム換算1秒)
bool		Character::c_stamina_draw		= false;	//スタミナの描画を切り替えるフラグ
bool		Character::found_flag			= true;		//発見される状態か判断するフラグ(透明化時に使用)

const float Character::scroll_width_space = 850;
const float Character::scroll_height_space = 300;

Character& Character::GetInstance(void)
{
	static Character	instance;
	return instance;
}

//初期化
void Character::Initialize(vivid::Vector2 rPos)
{
	accelerator = vivid::Vector2::ZERO;
	cPos = {100.0f, rPos.y - ch_height};
	chara_state = CHARA_STATE::WAIT;

	c_anchor	= {ch_width / 2,ch_height / 2 };
	c_scale		= {  1.0f,1.0f };
	c_rotate	= 0.0f;

	c_anime_frame = 0;
	c_anime_timer = 0;
	c_change_anime_timer = 6;
	c_change_anime_frame = 0;

	stamina_anchor = { ((float)stamina_width / 2.0f), ((float)stamina_height / 2.0f) };
	stamina_scale = { 1.0f, 1.0f };

	skill_active_flag = false;
	skill_cool_flag = false;
	active_count = 0;
	cool_time_count = 0;
	c_stamina_draw_count = 0;

	Scroll = { 0.0f, 0.0f };
}

void Character::Update(void)
{
	//自機のキーボード操作
	//KeyboardControl();
	//自機のコントローラー操作
	ControllerControl();
	//画面端の判定
	CheckWindow();
	//クールタイムの処理
	CoolTime();
	//ステージとの当たり判定
	StageHit();
	//アニメーションの更新
	UpdateAnimation();
	//スクロールの更新
	Scroll_Update();
	//スタミナの描画切り替え
	StaminaDraw();
}

//描画
void Character::Draw(void)
{
	//->スタミナの描画座標の更新
	stamina_pos.x = (float)(((cPos.x + (ch_width / 2.0f))- (stamina_width / 2.0f)));
	stamina_pos.y = (float)(cPos.y - 20);
	//<-スタミナの描画座標の更新

	//->自機のrect更新
	c_rect.top = 0;
	c_rect.bottom = ch_height;
	c_rect.left = ch_width * (c_anime_frame % c_change_anime_frame);
	c_rect.right = c_rect.left + ch_width;
	//<-自機のrect更新
	
	//->スタミナのrect更新
	stamina_rect.top = 0;
	stamina_rect.bottom = stamina_height;
	if (c_stamina_dash == true)
	{
		stamina_rect.left = stamina_width * (5 - c_stamina_gauge);
	}
	if (c_stamina_dash == false)
	{
		stamina_rect.left = stamina_width * c_stamina_gauge;
	}
	stamina_rect.right = stamina_rect.left + stamina_width;
	//<-スタミナのrect更新

	//自機の描画
	vivid::DrawTexture(c_image[(int)chara_skill][(int)chara_state], cPos - Scroll, color, c_rect, c_anchor, c_scale);
	//スタミナ描画フラグがtrueの時にのみスタミナゲージを描画する
	if (c_stamina_draw)
		vivid::DrawTexture(c_dash_image[c_stamina_dash], stamina_pos - Scroll, 0xffffffff, stamina_rect, stamina_anchor, stamina_scale);

	//デバッグモードの時に各必要情報を表示
#ifdef _DEBUG
	switch (chara_skill)
	{
	case CHARA_SKILL::NORMAL:
		vivid::DrawText(40, "ふつうだよー", vivid::Vector2(0.0f, 0.0f), 0xff00ffff);
		break;
	case CHARA_SKILL::ANIMALLEG:
		vivid::DrawText(40, "けものだよー", vivid::Vector2(0.0f, 0.0f), 0xff00ffff);
		break;
	case CHARA_SKILL::INVISIBLE:
		vivid::DrawText(40, "みえないよー", vivid::Vector2(0.0f, 0.0f), 0xff00ffff);
		break;
	}
	if (skill_active_flag == false)
		vivid::DrawText(40, "すきるつかってないよー", vivid::Vector2(0.0f, 50.0f), 0xff00ffff);
	if (skill_active_flag)
		vivid::DrawText(40, "すきるつかうよー", vivid::Vector2(0.0f, 50.0f), 0xff00ffff);
	if (skill_memory == (int)CHARA_SKILL::ANIMALLEG)
		vivid::DrawText(40, "あしつよいよー", vivid::Vector2(0.0f, 100.0f), 0xff00ffff);
	if (skill_memory == (int)CHARA_SKILL::INVISIBLE)
		vivid::DrawText(40, "めにみえないよー", vivid::Vector2(0.0f, 150.0f), 0xff00ffff);
	if (skill_cool_flag)
		vivid::DrawText(40, "スキルクールだよー", vivid::Vector2(0.0f, 200.0f), 0xff00ffff);
	vivid::DrawText(40,"キャラ速度：" +  std::to_string(m_Velocity.x), vivid::Vector2(0.0f, 250.0f), 0xff00ffff);
	vivid::DrawText(40, "キャラの色：" + std::to_string(color), vivid::Vector2(0.0f, 300.0f), 0xff00ffff);
	if (found_flag == true)
		vivid::DrawText(40, "視覚判定あるよー", vivid::Vector2(0.0f, 350.0f), 0xff00ffff);
	if (found_flag == false)
		vivid::DrawText(40, "視覚判定ないよー", vivid::Vector2(0.0f, 350.0f), 0xff00ffff);
#endif
}

//解放
void Character::Finalize(void)
{
}

//ステージの当たり判定
void Character::StageHit()
{
	//左
	if (cPos.x < Stage::GetInstance().GetLWall(cPos, ch_width, ch_height))
	{
		cPos.x = Stage::GetInstance().GetLWall(cPos, ch_width, ch_height);
	}
	//右
	if (cPos.x + ch_width > Stage::GetInstance().GetRWall(cPos, ch_width, ch_height))
	{
		cPos.x = Stage::GetInstance().GetRWall(cPos, ch_width, ch_height) - ch_width;
	}
	//天井
	if (cPos.y < Stage::GetInstance().GetCeiling(cPos, ch_width, ch_height))
	{	
		cPos.y = Stage::GetInstance().GetCeiling(cPos, ch_width, ch_height);
	}
	//地面
	RoundHit(Stage::GetInstance().GetRoundHeight(cPos, ch_width, ch_height));
}
void Character::HStageHit()
{
	//左
	if (cPos.x < Stage::GetInstance().GetLWall(cPos, ch_width, ch_height))
	{
		cPos.x = Stage::GetInstance().GetLWall(cPos, ch_width, ch_height);
	}
	//右
	if (cPos.x + ch_width > Stage::GetInstance().GetRWall(cPos, ch_width, ch_height))
	{
		cPos.x = Stage::GetInstance().GetRWall(cPos, ch_width, ch_height) - ch_width;
	}
}

//天井と地面の判定
void Character::VStageHit()
{
	//地面
	RoundHit(Stage::GetInstance().GetRoundHeight(cPos, ch_width, ch_height));
	//天井
	if (cPos.y < Stage::GetInstance().GetCeiling(cPos, ch_width, ch_height))
	{
		cPos.y = Stage::GetInstance().GetCeiling(cPos, ch_width, ch_height);
		m_Velocity.y = 0;
	}
}

//画面端の当たり判定
void Character::CheckWindow(void)
{
	//画面の左端
	if (cPos.x < 0.0f + Scroll.x)
	{
		cPos.x = 0.0f + Scroll.x;
	}
	//画面の右端
	if (cPos.x + ch_width > vivid::WINDOW_WIDTH + Scroll.x)
	{
		cPos.x = vivid::WINDOW_WIDTH - ch_width + Scroll.x;
	}
	//画面の天井
	if (cPos.y < 0.0f + Scroll.y)
	{
		cPos.y = 0.0f + Scroll.y;
	}
	//画面の底辺
	if (cPos.y + ch_height > vivid::WINDOW_HEIGHT + Scroll.y)
	{
		cPos.y = vivid::WINDOW_HEIGHT - ch_height + Scroll.y;
	}
}

//自機の操作
void Character::KeyboardControl(void)
{
	namespace keyboard = vivid::keyboard;

	accelerator = vivid::Vector2::ZERO;

	//デフォルトはwalk_speedにする
	ch_speed = walk_speed;

	//一定値を超えたら速度を0にして慣性の移動を止める
	if (abs(m_Velocity.x) < cut_speed)
	{
		m_Velocity.x = 0.0f;
		if (m_LandingFlag)
		{
			chara_state = CHARA_STATE::WAIT;
		}
	}
	//デフォルトは待機状態にする
	if (m_LandingFlag)
		chara_state = CHARA_STATE::WAIT;

	//左SHIFTを押している間はdash_speedになる
	if (keyboard::Button(keyboard::KEY_ID::LSHIFT))
	{
		ch_speed = dash_speed;
		if (m_LandingFlag)
			chara_state = CHARA_STATE::WAIT;
	}

	//左CTRLを押している間はsneak_speedになる
	if (keyboard::Button(keyboard::KEY_ID::LCONTROL))
	{
		ch_speed = sneak_speed;
		if (m_LandingFlag)
			chara_state = CHARA_STATE::SNEAKWAIT;
	}

	//スタミナが0ではなく走っていない時はスタミナが回復する
	if (!(chara_state == CHARA_STATE::RUN) && c_stamina_dash)
	{
		RecoveryStamina();
	}

	//スタミナゲージが0の時はfatigue_speedになる
	if (!c_stamina_dash)
	{
		LimitStamina();
	}

	//Eキーを押すとスキルが切り替わる
	if (keyboard::Trigger(keyboard::KEY_ID::E))
	{
		ChangeSkill();
	}

	//Aを押している間は左移動
	if (keyboard::Button(keyboard::KEY_ID::A))
	{
		accelerator.x = -ch_speed;
		c_scale.x = -1.0f;
		//ダッシュ中のスタミナ処理
		if (ch_speed == dash_speed && c_stamina_dash)
		{
			DashStamina();
		}

		CheckMoveState();
	}

	//Dを押している間は右移動
	if (keyboard::Button(keyboard::KEY_ID::D))
	{
		accelerator.x = ch_speed;
		c_scale.x = 1.0f;
		//ダッシュ中のスタミナ処理
		if (ch_speed == dash_speed && c_stamina_dash)
		{
			DashStamina();
		}

		CheckMoveState();
	}

	//ジャンプの処理
	//SPACEを押すとジャンプ動作になる
	if (keyboard::Trigger(keyboard::KEY_ID::SPACE) && m_LandingFlag)
	{
		accelerator.y += jump_speed;
		chara_state = CHARA_STATE::JUMP;
	}

	//Qキーを押すとスキルが発動する
	if (keyboard::Trigger(keyboard::KEY_ID::Q))
	{
		//重複しないようにするためにフラグを通す
		if (skill_active_flag == false && skill_cool_flag == false)
		{
			skill_active_flag = true;
		}
	}

	//スキルの動作処理
	SkillMove();

	//落下処理
	if (m_LandingFlag == false||1)
	{
		accelerator.y += fall_speed;
	}

	//置き換えた座標を代入する
	m_Velocity += accelerator;
	cPos.x += m_Velocity.x;
	//ステージとの当たり判定の確認
	HStageHit();

	cPos.y += m_Velocity.y;

	VStageHit();

	//画面端の判定
	CheckWindow();

	//移動に慣性をつける
	m_Velocity.x *= m_friction;
}

void Character::ControllerControl(void)
{
	namespace controller = vivid::controller;

	accelerator = vivid::Vector2::ZERO;

	//デフォルトはwalk_speedにする
	ch_speed = walk_speed;

	//一定値を超えたら速度を0にして慣性の移動を止める
	if (abs(m_Velocity.x) < cut_speed)
	{
		m_Velocity.x = 0.0f;
		if (m_LandingFlag)
		{
			chara_state = CHARA_STATE::WAIT;
		}
	}
	//デフォルトは待機状態にする
	if (m_LandingFlag)
		chara_state = CHARA_STATE::WAIT;

	//Aボタンを長押しでダッシュする
	if (controller::Button(controller::DEVICE_ID::PLAYER1, controller::BUTTON_ID::A))
	{
		ch_speed = dash_speed;
		if (m_LandingFlag)
			chara_state = CHARA_STATE::WAIT;
	}

	//下ボタンを長押しでしゃがみになる
	if (controller::Button(controller::DEVICE_ID::PLAYER1, controller::BUTTON_ID::DOWN))
	{
		ch_speed = sneak_speed;
		if (m_LandingFlag)
			chara_state = CHARA_STATE::SNEAKWAIT;
	}
	
	//スタミナが0ではなく走っていない時はスタミナが回復する
	if (!(chara_state == CHARA_STATE::RUN) && c_stamina_dash)
	{
		RecoveryStamina();
	}

	//スタミナゲージが0の時はfatigue_speedになる
	if (!c_stamina_dash)
	{
		LimitStamina();
	}
	//Yボタンを押したらスキルが切り替わる
	if (controller::Trigger(controller::DEVICE_ID::PLAYER1, controller::BUTTON_ID::Y))
	{
		ChangeSkill();
	}
	//十字左長押しで左移動
	if (controller::Button(controller::DEVICE_ID::PLAYER1, controller::BUTTON_ID::LEFT))
	{
		accelerator.x = -ch_speed;
		c_scale.x = -1.0f;
		//ダッシュ中のスタミナ処理
		if (ch_speed == dash_speed && c_stamina_dash)
		{
			DashStamina();
		}

		CheckMoveState();
	}
	//十字右長押しで右移動
	if (controller::Button(controller::DEVICE_ID::PLAYER1, controller::BUTTON_ID::RIGHT))
	{
		accelerator.x = ch_speed;
		c_scale.x = 1.0f;
		//ダッシュ中のスタミナ処理
		if (ch_speed == dash_speed && c_stamina_dash)
		{
			DashStamina();
		}

		CheckMoveState();
	}

	//Bボタンを押すとジャンプをする
	if ((controller::Trigger(controller::DEVICE_ID::PLAYER1, controller::BUTTON_ID::B)) && m_LandingFlag)
	{
		accelerator.y += jump_speed;
		chara_state = CHARA_STATE::JUMP;
	}
	//Xボタンを押すとスキルが発動する
	if (controller::Trigger(controller::DEVICE_ID::PLAYER1, controller::BUTTON_ID::X))
	{
		//重複しないようにするためにフラグを通す
		if (skill_active_flag == false && skill_cool_flag == false)
		{
			skill_active_flag = true;
		}
	}
	
	//スキルの動作処理
	SkillMove();

	//落下処理
	if (m_LandingFlag == false || 1)
	{
		accelerator.y += fall_speed;
	}

	//置き換えた座標を代入する
	m_Velocity += accelerator;
	cPos.x += m_Velocity.x;
	//ステージとの当たり判定の確認
	HStageHit();

	cPos.y += m_Velocity.y;

	VStageHit();

	//画面端の判定
	CheckWindow();

	//移動に慣性をつける
	m_Velocity.x *= m_friction;
}

//地面との当たり判定
void Character::RoundHit(float rHeight)
{
	if (cPos.y + ch_height < rHeight)
	{
		m_LandingFlag = false;
	}
		if (cPos.y + ch_height > rHeight && cPos.y < rHeight) {
			cPos.y = rHeight - ch_height;
			m_Velocity.y = 0.0f;
			//地面と当たったら接地フラグをtrueにする
			m_LandingFlag = true;
		}
}

//壁の裏に自機がすべて隠れていたら色を変える
bool Character::CheckWallHit(vivid::Vector2 wPos, float wWidth, float wHeight)
{
	return Stage::GetInstance().CheckHitWallPlayer(cPos, ch_height, ch_width);
	if ((wPos.x <= cPos.x) && (wPos.x + wWidth >= cPos.x + ch_width) && (wPos.y <= cPos.y) && (wPos.y + wHeight >= cPos.y + ch_height))
	{
		return true;
	}
	else
	{
		return false;
	}
}

//敵の視界に入ったらtrueを返す、視界の外の時はfalseを返す
bool Character::CheckEnemyHit(vivid::Vector2 ePos, float eRadius)
{
	//点と矩形の判定その1(横長)
	bool result_h = ePos.x > cPos.x - eRadius
		&& ePos.x < cPos.x + ch_width + eRadius
		&& ePos.y > cPos.y
		&& ePos.y < cPos.y + ch_height;

	//点と矩形の判定その2(縦長)
	bool result_v = ePos.x > cPos.x
		&& ePos.x < cPos.x + ch_width
		&& ePos.y > cPos.y - eRadius
		&& ePos.y < cPos.y + ch_height + eRadius;

	//点と円の判定	
	//自機の左上(LeftUpper)
	vivid::Vector2 v = ePos - cPos;
	bool result_lu = v.Length() <= eRadius;		
	//自機の右上(RightUpper)
	v = ePos - vivid::Vector2(cPos.x + ch_width, cPos.y);
	bool result_ru = v.Length() <= eRadius;
	//自機の左下(LeftDown)
	v = ePos - vivid::Vector2(cPos.x, cPos.y + ch_height);
	bool result_ld = v.Length() <= eRadius;
	//自機の右下(RightDown)
	v = ePos - vivid::Vector2(cPos.x + ch_width, cPos.y + ch_height);
	bool result_rd = v.Length() <= eRadius;
	//上記の判定から当たっているか(視界に入っているか)を判断する
	if (result_h || result_v || result_lu || result_ru || result_ld || result_rd)
	{
		if (found_flag == false)
		{
			return false;
		}
		return true;
	}
	//当たっていない場合はfalseを返す
	else
	{
		return false;
	}
}

//アイテムとの当たり判定
bool Character::CheckObtainItem(vivid::Vector2 iPos, vivid::Vector2 iCenter, float iWidth, float iHeight)
{
	//対角線とベクトルで処理を行う(単ブロックに使用推奨)
	float a1 = -iHeight / iWidth;
	float a2 = iHeight / iWidth;
	float a3 = (cPos.y - iCenter.y) / (cPos.x - iPos.x);

	if (cPos.x < iPos.x + iWidth && cPos.x + ch_width > iPos.x
		&& cPos.y < iPos.y + iHeight && cPos.y + ch_height > iPos.y)
	{
		if (vivid::keyboard::Trigger(vivid::keyboard::KEY_ID::F))
		{
			cCatch = true;
			return true;
		}
	}
	return false;
}

//当たった時にそれぞれ色を変える
void Character::CheckHit(vivid::Vector2 wPos, float wWidth, float wHeight, vivid::Vector2 ePos, float eRadius)
{
	//壁に当たった時(障害物に隠れたとき)
	if (CheckWallHit(wPos, wWidth, wHeight))
	{
#ifdef _DEGUB
		color = 0xff0000ff;
#endif // DEBUG
	}
	//障害物の外で敵の視界に入った時
	else if (CheckEnemyHit(ePos, eRadius))
	{
#ifdef _DEBUG
		color = 0xffff0000;
#endif // DEBUG
	}
	//デフォルトの状態
	else
	{
#ifdef _DEBUG
		color = 0xffffffff;
#endif // DEBUG
	}
}

//敵や障害物との当たり判定
void Character::CheckHit(vivid::Vector2 wPos, float wWidth, float wHeight, bool EnemyHitFlg)
{	
	//壁に当たった時(障害物に隠れたとき)
	if (CheckWallHit(wPos, wWidth, wHeight))
	{
#ifdef _DEBUG
		color = 0xff0000ff;
#endif // DEBUG
		cShielding = true;
	}
	//障害物の外で敵の視界に入った時
	else if (EnemyHitFlg)
	{
#ifdef _DEBUG
		color = 0xffff0000;
#endif // DEBUG
		cShielding = false;
	}
	//デフォルトの状態
	else
	{
#ifdef _DEBUG
		color = 0xffffffff;
#endif // DEBUG
		cShielding = false;
	}
}

//投げた動作を実行したかを返すフラグ
bool Character::CheckThrow(void)
{
	if (cCatch)
	{
		if (vivid::keyboard::Trigger(vivid::keyboard::KEY_ID::C))
		{
			return true;
		}
		return false;
	}
}

//アイテムを置く動作を実行したかを返す
bool Character::checkPut(void)
{
	if (cCatch)
	{
		if (vivid::keyboard::Trigger(vivid::keyboard::KEY_ID::R))
		{
			return true;
		}
		return false;
	}
}

//アニメーションの更新
void Character::UpdateAnimation(void)
{
	//状態ごとにアニメーションの最大枚数の設定
	switch (chara_state)
	{
	case CHARA_STATE::WAIT:
		c_change_anime_frame = 12;
		break;
	case CHARA_STATE::WALK:
		c_change_anime_frame = 18;
		break;
	case CHARA_STATE::RUN:
		c_change_anime_frame = 9;
		break;
	case CHARA_STATE::SNEAKWAIT:
		c_change_anime_frame = 12;
		break;
	case CHARA_STATE::SNEAKWALK:
		c_change_anime_frame = 15;
		break;
	case CHARA_STATE::JUMP:
		c_change_anime_frame = 8;
		break;
	}

	//->アニメーションの更新
	c_anime_timer++;

	if (c_anime_timer >= c_change_anime_timer)
	{
		c_anime_frame++;
		if (c_anime_frame == c_change_anime_frame)
		{
			c_anime_frame = 0;
		}
		c_anime_timer = 0;
	}
	//<-アニメーションの更新
}

//自機が接地している状態の変更処理
void Character::CheckMoveState(void)
{
	if (m_LandingFlag)
	{
		chara_state = CHARA_STATE::WALK;
		if (ch_speed == dash_speed)
		{
			chara_state = CHARA_STATE::RUN;
		}
		if (ch_speed == sneak_speed)
		{
			chara_state = CHARA_STATE::SNEAKWALK;
		}
	}
}

//スタミナの消費処理
void Character::DashStamina(void)
{
	//スタミナゲージに残量がある時かの確認
	if (c_stamina_gauge > 0)
	{
	//スタミナ消費のカウンタを進める
		c_stamina_count++;
	//カウンタが基準値に達したらスタミナゲージ減らす
		if (c_stamina_count >= 60)
		{
			c_stamina_gauge--;
			c_stamina_count = 0;
		}
	}
	//スタミナが0になった後の処理
	else
	{
		c_stamina_dash = false;
	}
	//スタミナ回復開始のカウンタのリセット
	c_stamina_recovery = 0;
}

//スタミナの回復処理
void Character::RecoveryStamina(void)
{
	c_stamina_recovery++;
	if (c_stamina_gauge < c_max_stamina)
	{
		if (c_stamina_recovery >= 60)
		{
			c_stamina_gauge++;
			c_stamina_count = 0;
			c_stamina_recovery = 0;
		}
	}
}

//スタミナが0になった後の回復処理
void Character::LimitStamina(void)
{
	ch_speed = fatigue_speed;
	c_limit_recovery++;
	if (c_limit_recovery >= 90)
	{
		if (c_stamina_gauge < c_max_stamina)
		{
			c_stamina_gauge++;
			c_limit_recovery = 0;
		}
		if (c_stamina_gauge == c_max_stamina)
		{
			c_stamina_dash = true;
		}
	}
}

//スキル発動後の処理
void Character::SkillMove(void)
{
	//スキルのアクティブフラグがtrueの時に処理を行う
	if (skill_active_flag)
	{
		active_count++;
		if (active_count < activation_time)
		{
			switch ((skill_memory))
			{
			case (int)CHARA_SKILL::ANIMALLEG:
				accelerator *= 1.6f;
				chara_skill = CHARA_SKILL::ANIMALLEG;
				break;
			case (int)CHARA_SKILL::INVISIBLE:
				chara_skill = CHARA_SKILL::INVISIBLE;
				color = 0x44ffffff;
				found_flag = false;
				break;
			}
		}
		//タイマーが規定値を超えたら各数値をリセットする
		if (active_count >= activation_time)
		{
			switch (skill_memory)
			{
			case (int)CHARA_SKILL::ANIMALLEG:
				accelerator *= 0.625f;
				break;
			case (int)CHARA_SKILL::INVISIBLE:
				color = 0xffffffff;
				found_flag = true;
				break;
			default:
				break;
			}
			chara_skill = CHARA_SKILL::NORMAL;
			active_count = 0;
			skill_active_flag = false;
			skill_cool_flag = true;
		}
	}
}

//スキルの切り替え処理
void Character::ChangeSkill(void)
{
	if (skill_active_flag == false)
	{
		switch (skill_memory)
		{
		case (int)CHARA_SKILL::INVISIBLE:
			skill_memory = (int)CHARA_SKILL::ANIMALLEG;
			break;

		case (int)CHARA_SKILL::ANIMALLEG:
			skill_memory = (int)CHARA_SKILL::INVISIBLE;
			break;
		}
	}
}

//スキルのクールタイム処理
void Character::CoolTime(void)
{
	if (skill_cool_flag)
	{
		cool_time_count++;
		if (cool_time_count >= skill_cool_time)
		{
			cool_time_count = 0;
			skill_cool_flag = false;
		}
	}
}

//スタミナの描画を切り替える処理
void Character::StaminaDraw(void)
{
	namespace keyboard = vivid::keyboard;
	namespace controller = vivid::controller;

	//ダッシュボタンを押している間は描画フラグをtrueにして描画カウンタをリセットする
	if ((keyboard::Button(keyboard::KEY_ID::LSHIFT)) || (controller::Button(controller::DEVICE_ID::PLAYER1, controller::BUTTON_ID::A)))
	{
		c_stamina_draw = true;
		c_stamina_draw_count = 0;
	}
	//押していない時にスタミナが最大値だったらカウンタを進め、規定値に達したら描画フラグをfalseにしてカウンタをリセットする
	else
	{
		if (c_stamina_gauge == c_max_stamina)
		{
			c_stamina_draw_count++;
			if (c_stamina_draw_count >= c_draw_stamina)
			{
				c_stamina_draw = false;
				c_stamina_draw_count = 0;
			}
		}
	}
}

//スクロールの更新
void Character::Scroll_Update()
{
	if (cPos.x > Scroll.x + vivid::WINDOW_WIDTH - scroll_width_space)
		Scroll.x = cPos.x - vivid::WINDOW_WIDTH + scroll_width_space;
	if (Scroll.x > Stage::GetInstance().GetStageWidthSize() - vivid::WINDOW_WIDTH)
		Scroll.x = Stage::GetInstance().GetStageWidthSize() - vivid::WINDOW_WIDTH;
	if (cPos.x < Scroll.x + scroll_width_space)
		Scroll.x = cPos.x - scroll_width_space;
	if (Scroll.x < 0)
		Scroll.x = 0;

	if (cPos.y > Scroll.y + vivid::WINDOW_HEIGHT - scroll_height_space)
		Scroll.y = cPos.y - vivid::WINDOW_HEIGHT + scroll_height_space;
	if (Scroll.y > Stage::GetInstance().GetStageHeightSize() - vivid::WINDOW_HEIGHT)
		Scroll.y = Stage::GetInstance().GetStageHeightSize() - vivid::WINDOW_HEIGHT;
	if (cPos.y < Scroll.y + scroll_height_space)
		Scroll.y = cPos.y - scroll_height_space;
	if (Scroll.y < 0)
		Scroll.y = 0;
}