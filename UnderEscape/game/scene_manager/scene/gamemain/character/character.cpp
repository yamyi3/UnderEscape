#include "character.h"
#include "../stage/stage.h"

float	Character::ch_speed = walk_speed;
unsigned Character::color = 0xffffffff;
bool	Character::m_LandingFlag = false;
bool	Character::cCatch = false;
bool	Character::cAlive = true;
int		Character::gauge = 0;
int		Character::gauge_count_frame = 0;
int		Character::down_gauge_count = 0;

const float Character::run_speed = 1.0f;		//自機の通常移動速度
const float Character::dash_speed = 1.5f;		//自機のダッシュ時の移動速度
const float Character::walk_speed = 0.5f;		//自機の歩行時の移動速度

Character& Character::GetInstance(void)
{
	static Character	instance;
	return instance;
}

void Character::Initialize(vivid::Vector2 rPos)
{
	cPos = {100.0f, rPos.y - ch_height};
	gPos = { 0.0f, 0.0f };
	gauge_rect.top = 0;
	gauge_rect.bottom = 30;
	gauge_rect.left = 0;
	gauge_rect.right = 20 * gauge;
}

void Character::Update(void)
{
	Control();
	CheckWindow();
}

void Character::Draw(void)
{
	vivid::Rect rect;
	rect.top = 0;
	rect.bottom = 30;
	rect.left = 0;
	rect.right = 200;

	gauge_rect.top = 0;
	gauge_rect.bottom = 30;
	gauge_rect.left = 0;
	gauge_rect.right = 20 * gauge;

	vivid::DrawTexture("data\\minihuman透過1.png", cPos, color);
	vivid::DrawTexture("data\\gauge.png", gPos, 0xffffffff, rect);
	vivid::DrawTexture("data\\gauge.png", gPos, 0xff00ffff, gauge_rect);
}

void Character::Finalize(void)
{
}

//画面端の当たり判定
void Character::CheckWindow(void)
{
	//画面の左端
	if (cPos.x < 0.0f)
	{
		cPos.x = 0.0f;
	}
	//画面の右端
	if (cPos.x + ch_width > vivid::WINDOW_WIDTH)
	{
		cPos.x = vivid::WINDOW_WIDTH - ch_width;
	}
	//画面の天井
	if (cPos.y < 0.0f)
	{
		cPos.y = 0.0f;
	}
	//画面の底辺
	if (cPos.y + ch_height > vivid::WINDOW_HEIGHT)
	{
		cPos.y = vivid::WINDOW_HEIGHT - ch_height;
	}
}

//自機の操作
void Character::Control(void)
{
	namespace keyboard = vivid::keyboard;

	vivid::Vector2 accelerator = {};

	//デフォルトはwalk_speedにする
	ch_speed = run_speed;
	//左SHIFTを押している間はrun_speedになる
	if (keyboard::Button(keyboard::KEY_ID::LSHIFT))
	{
		ch_speed = dash_speed;
	}
	//左CTRLを押している間はwalk_speedになる
	if (keyboard::Button(keyboard::KEY_ID::LCONTROL))
	{
		ch_speed = walk_speed;
	}
	//Aを押している間は左移動
	if (keyboard::Button(keyboard::KEY_ID::A))
	{
		accelerator.x = -ch_speed;
	}
	//Dを押している間は右移動
	if (keyboard::Button(keyboard::KEY_ID::D))
	{
		accelerator.x = ch_speed;
	}

	if (cCatch)
	{
		if (keyboard::Trigger(keyboard::KEY_ID::C))
		{

		}
	}
	
	//ジャンプの処理
	//SPACEを押すとジャンプ動作になる
	if (keyboard::Trigger(keyboard::KEY_ID::SPACE) && m_LandingFlag)
	{
		accelerator.y += jump_speed;
		//接地フラグをfalseにして空中ジャンプを出来ないようにする
		m_LandingFlag = false;
	}

	//落下処理
	if (m_LandingFlag == false)
	{
		accelerator.y += fall_speed;
	}

	m_Velocity += accelerator;
	cPos += m_Velocity;

	//移動に慣性をつける
	m_Velocity.x *= m_friction;

	//一定値を超えたら速度を0にして慣性の移動を止める
	if (abs(m_Velocity.x) < cut_speed)
	{
		m_Velocity.x = 0.0f;
	}
}

//地面との当たり判定
void Character::RoundHit(vivid::Vector2 rPos)
{
		if (cPos.y + ch_height > rPos.y && cPos.y < rPos.y) {
			cPos.y = rPos.y - ch_height;
			m_Velocity.y = 0.0f;
			//地面と当たったら接地フラグをtrueにする
			m_LandingFlag = true;
		}
}

//壁の裏に自機がすべて隠れていたら色を変える
bool Character::CheckWallHit(vivid::Vector2 wPos, float wWidth, float wHeight)
{
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
		return true;
	}
	//当たっていない場合はfalseを返す
	else
	{
		return false;
	}
}

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
		DownerGauge();
		color = 0xff0000ff;
	}
	//障害物の外で敵の視界に入った時
	else if (CheckEnemyHit(ePos, eRadius))
	{
		UpperGauge();
		color = 0xffff0000;
	}
	//デフォルトの状態
	else
	{
		DownerGauge();
		color = 0xffffffff;
	}
}

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

void Character::UpperGauge(void)
{
	down_gauge_count = 0;
	gauge_count_frame++;
	if (gauge_count_frame == one_gauge_frame)
	{
		if (gauge < max_gauge)
		{
			gauge++;
			gauge_count_frame = 0;
		}
		if (gauge >= max_gauge)
		{
			//終わり
			vivid::DrawText(40, "おわりだよー", vivid::Vector2(800.0f, 500.0f));
		}
	}
}

void Character::DownerGauge(void)
{
	down_gauge_count++;
	if (down_gauge_count >= downer_frame)
	{
		if (gauge > 0)
		{
			gauge--;
		}
		down_gauge_count = 0;
	}
}
