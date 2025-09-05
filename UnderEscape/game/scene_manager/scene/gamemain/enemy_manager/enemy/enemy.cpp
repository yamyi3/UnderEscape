//enemy.cpp

#include "enemy.h"
#include "..\..\stage\stage.h"
#include"..\..\item_manager\item_manager.h"
#include"..\..\item_manager\item\item.h"

const int Enemy::e_visibility_width_size = 400;
const int Enemy::e_visibility_height_size = 400;


const int Enemy::mark_width_size = 32;		//!の横のドット数
const int Enemy::mark_height_size = 32;      //!の縦のドット数

const int Enemy::Source_End_Range = 4;				//警戒座標とのｘ軸の差がこの数値より短くなったら追跡を終了する。
const int Enemy::Vigilance_time = 150;				//追跡目標地点到達後の待機フレーム数

const int Enemy::Surprised_time = 30;				//追跡開始前の停止フレーム数

const int Enemy::turn_around_ct = 10;

const int Enemy::animation_change_time = 5;




Enemy::Enemy(int w_size ,int h_size,float speed,float chase_speed,
	float jump_height,float jump_upspeed,float jump_downspeed,float circle_radius)
	: e_width_size(w_size)
	, e_height_size(h_size)
	, eSpeed(speed)
	, eChaseSpeed(chase_speed)
	, enemy_jump_height(jump_height)
	, enemy_jump_upspeed(jump_upspeed)
	, enemy_jump_downspeed(jump_downspeed)
	, eCircleRadius(circle_radius)
	, ePos(300.0f, 500.0f)
	, eAnchor(e_width_size / 2.0f, e_height_size / 2.0f)
	, eScale(1.0f, 1.0f)
	, markPos(0.0f, 0.0f)
	, markAnchor(mark_width_size / 2.0f, mark_height_size / 2.0f)
	, markScale(1.0, 1.0)
	, gravity(100)
	, eGround(60000.0f)
	, eVector(1)
	, Sight_Check_Timer(10)
	, Vigilance_Timer(0)
	, Surprised_Timer(0)
	, eStatus(eSTATUS::Wandering)
	, m_ActiveFlag(true)
	, WallTouchFlg(false)
	, WallTouchPosX(0.0f)
	, AnimationTimer(0)
	, AnimationFrame(0)

	, item_area(false)
	, item_pos({ 0.0f, 0.0f })

	, TurnAroundtimer(10)

{
}
void Enemy::Initialize(vivid::Vector2 pos, float L, float R, float vector, float ground)
{
	eGround = ground;
	if (L == R)
		eStatus = eSTATUS::Stop;
	if (L > R)
	{
		Initialize(pos, R, L, vector, ground);
	}
	else
	{
		ePos = pos;
		eGround = ground;
		Rwall = R;
		Lwall = L;
		eVector = vector;
		gravity = 100;
		jpflg = 0;
		eCircleCenterPos.x = ePos.x - e_width_size / 2;
		eCircleCenterPos.y = ePos.y - e_height_size / 2;
	}

	AnimationTimer = 0;
	AnimationFrame = 0;


}

void Enemy::Initialize(vivid::Vector2 pos, float L, float R, float vector)
{
	Initialize(pos, L, R, vector, 60000.0f);
}

void Enemy::Initialize(vivid::Vector2 pos, float L, float R)
{
	Initialize(pos, L, R, 1, 60000.0f);
}
void Enemy::Initialize(vivid::Vector2 pos)
{
	Initialize(pos, pos.x, pos.x, 1, 60000.0f);
}
void Enemy::Initialize(void)
{
	Enemy::Initialize({ 300.0f, 500.0f }, 300.0f, 600.0f);
}

void Enemy::Update(void)
{
	if (ItemManager::GetInstance().GetItemID() == ITEM_ID::FLASH_ITEM)
	{
		item_pos = ItemManager::GetInstance().GetItemPos();
		item_pos.x = abs((item_pos.x) - ePos.x);										//アイテムとエネミーの横の距離
		item_pos.y = abs((item_pos.y) - ePos.y);										//アイテムとエネミーの縦の距離
		if (ItemManager::GetInstance().GetItemActiveFlag() == true)		//平方根で距離を求め比べる 300は効果範囲
		{
			if (sqrt((item_pos.x * item_pos.x) + (item_pos.y * item_pos.y)) <= 300)
			{
				Surprised_Timer = 0;	//アイテムの効果範囲内にいる場合はSurprised_Timerをリセット
				Vigilance_Timer = 0; 	//アイテムの効果範囲内にいる場合はVigilance_Timerをリセット
				eStatus = eSTATUS::Surprised;
			}
		}
	}
	if (ItemManager::GetInstance().GetItemID() == ITEM_ID::SOUND_ITEM)
	{
		if (ItemManager::GetInstance().GetItemActiveFlag() == true)
		{
			sound_sensor(ItemManager::GetInstance().GetItemPos(), 500);
		}
	}

	//switch (ItemManager::GetInstance().GetItemID())
	//{
	//case ITEM_ID::FLASH_ITEM:	//閃光弾
	//	item_pos = ItemManager::GetInstance().GetItemPos();
	//	item_pos.x = abs((item_pos.x) - ePos.x);										//アイテムとエネミーの横の距離
	//	item_pos.y = abs((item_pos.y) - ePos.y);										//アイテムとエネミーの縦の距離
	//	if (ItemManager::GetInstance().GetItemActiveFlag() == true)		//平方根で距離を求め比べる 300は効果範囲
	//	{
	//		if (sqrt((item_pos.x * item_pos.x) + (item_pos.y * item_pos.y)) <= 300)
	//		{
	//			Surprised_Timer = 0;	//アイテムの効果範囲内にいる場合はSurprised_Timerをリセット
	//			Vigilance_Timer = 0; 	//アイテムの効果範囲内にいる場合はVigilance_Timerをリセット
	//			eStatus = eSTATUS::Surprised;
	//		}
	//	}

	//	break;
	//case ITEM_ID::SOUND_ITEM:	//音爆弾
	//	if (ItemManager::GetInstance().GetItemActiveFlag() == true)		
	//	{
	//		sound_sensor(ItemManager::GetInstance().GetItemPos(), 500);
	//	}
	//	break;
	//default:
	//	break;
	//}


	Sight_Check_Timer++;
	vivid::Vector2 e_Velocity = { 0.0f,0.0f };
	switch (eStatus)
	{
	case eSTATUS::Stop:
		break;
	case eSTATUS::Wandering:
		if (eVector == 1)
		{
			e_Velocity.x += eSpeed;
			if (ePos.x + e_Velocity.x >= Rwall)
			{
				eVector = -1;
				if (Lwall == Rwall)
					eStatus = eSTATUS::Stop;
			}
		}
		else
		{
			e_Velocity.x -= eSpeed;
			if (ePos.x + e_Velocity.x <= Lwall)
			{
				eVector = 1;
				if (Lwall == Rwall)
					eStatus = eSTATUS::Stop;
			}
		}
		break;
	case eSTATUS::Chase:



		if (ChasePos.x > ePos.x)
		{
			if (abs(ChasePos.x - ePos.x) > Source_End_Range)
			{
				e_Velocity.x += eChaseSpeed;
				eVector = 1;
			}
		}
		else
		{
			if (abs(ChasePos.x - ePos.x) > Source_End_Range)
			{
				e_Velocity.x -= eChaseSpeed;
				eVector = -1;
			}
		}
		if (abs(ChasePos.x - ePos.x + e_Velocity.x) < Source_End_Range)
		{
			if (Sight_Check_Timer >= 10)
			{
				Vigilance_Timer = 0;
				eStatus = eSTATUS::Vigilance;
			}
		}

		break;
	case eSTATUS::Vigilance:
		if (++Vigilance_Timer >= Vigilance_time)
		{
			if (Lwall == Rwall)
				eStatus = eSTATUS::Stop;
			else
				eStatus = eSTATUS::Wandering;
		}
		break;
	case eSTATUS::Surprised:


		if (++Surprised_Timer >= Surprised_time)
		{
			eStatus = eSTATUS::Chase;

			//if (ItemManager::GetInstance().GetItemActiveFlag() == false)
			//{
			//	eStatus = eSTATUS::Chase;

			//}
			//else
			//{
			//	eStatus = eSTATUS::Vigilance;
			//}
		}

		break;
	default:
		break;
	}

	//地面
	if (ePos.y > Stage::GetInstance().GetRoundHeight(ePos, e_width_size, e_height_size, eAnchor))
	{
		ePos.y = Stage::GetInstance().GetRoundHeight(ePos, e_width_size, e_height_size, eAnchor);
	}
	bool TurnAroundFlg = false;
	TurnAroundtimer++;

	//天井
	if (ePos.y < Stage::GetInstance().GetCeiling(ePos, e_width_size, e_height_size, eAnchor))
	{
		ePos.y = Stage::GetInstance().GetCeiling(ePos, e_width_size, e_height_size, eAnchor);
	}	
	//左
	ePos.x += e_Velocity.x;
	if (ePos.x < Stage::GetInstance().GetLWall(ePos, e_width_size, e_height_size, eAnchor))
	{
		ePos.x = Stage::GetInstance().GetLWall(ePos, e_width_size, e_height_size, eAnchor);
		TurnAroundFlg = true;
	}
	//右
	if (ePos.x > Stage::GetInstance().GetRWall(ePos, e_width_size, e_height_size, eAnchor))
	{
		ePos.x = Stage::GetInstance().GetRWall(ePos, e_width_size, e_height_size, eAnchor);
		TurnAroundFlg = true;
	}
	if (TurnAroundFlg && TurnAroundtimer >= 10)
	{
		eVector *= -1;
		TurnAroundtimer = 0;
	}
	eGround = Stage::GetInstance().GetRoundHeight(ePos, e_width_size, e_height_size);

	if (e_wool_jump())
	{
		jump();
	}

	ePos = Gravity(ePos, eGround, e_height_size, eAnchor, enemy_jump_height, enemy_jump_upspeed, enemy_jump_downspeed);

	eCircleCenterPos.x = ePos.x - e_width_size / 2/* + eCircleRadius*/;
	eCircleCenterPos.y = ePos.y - e_height_size / 2/* + eCircleRadius*/;
}

void Enemy::Draw(vivid::Vector2 scroll)
{


}

void Enemy::Finalize(void)
{
}

vivid::Vector2 Enemy::GetEnemyPos(void)
{
	return ePos;
}

float Enemy::GetCircleRadius(void)
{
	return eCircleRadius;
}

vivid::Vector2 Enemy::GetCircleCenterPos(void)
{
	return eCircleCenterPos;
}

bool Enemy::CheckHitPlayer(const vivid::Vector2& cPos, int c_height, int c_width)
{

	//点と矩形の判定その1(横長)
	bool result_h = ePos.x > cPos.x - eCircleRadius
		&& ePos.x < cPos.x + c_width + eCircleRadius
		&& ePos.y > cPos.y
		&& ePos.y < cPos.y + c_height;

	//点と矩形の判定その2(縦長)
	bool result_v = ePos.x > cPos.x
		&& ePos.x < cPos.x + c_width
		&& ePos.y > cPos.y - eCircleRadius
		&& ePos.y < cPos.y + c_height + eCircleRadius;

	//点と円の判定	
	//自機の左上(LeftUpper)
	vivid::Vector2 v = ePos - cPos;
	bool result_lu = v.Length() <= eCircleRadius;
	//自機の右上(RightUpper)
	v = ePos - vivid::Vector2(cPos.x + c_width, cPos.y);
	bool result_ru = v.Length() <= eCircleRadius;
	//自機の左下(LeftDown)
	v = ePos - vivid::Vector2(cPos.x, cPos.y + c_height);
	bool result_ld = v.Length() <= eCircleRadius;
	//自機の右下(RightDown)
	v = ePos - vivid::Vector2(cPos.x + c_width, cPos.y + c_height);
	bool result_rd = v.Length() <= eCircleRadius;
	//上記の判定から当たっているか(視界に入っているか)を判断する
	if (result_h || result_v || result_lu || result_ru || result_ld || result_rd)
	{
		Sight_Check_Timer = 0;
		eChaseStatus = eCHASE_STATUS::Hearing;
		if (eStatus == eSTATUS::Wandering || eStatus == eSTATUS::Vigilance)
		{
			eStatus = eSTATUS::Surprised;
			Surprised_Timer = 0;
		}

		ChasePos = cPos;
		return true;
	}
	//当たっていない場合はfalseを返す
	else
	{
		return false;
	}
}

//音の判定
void Enemy::sound_sensor(vivid::Vector2 sound_source, float sound_size)
{
	float sound_work = 1.0f;														//音の大きさの倍率
	vivid::Vector2 work;															//音源とエネミーの距離を測るのに使う
	work.x = abs(sound_source.x - ePos.x);										//音源とエネミーの横の距離
	work.y = abs(sound_source.y - ePos.y);										//音源とエネミーの縦の距離
	if (sqrt((work.x * work.x) + (work.y * work.y)) <= sound_size * sound_work)		//平方根で距離を求め比べる
	{
		if (eStatus == eSTATUS::Wandering || eStatus == eSTATUS::Vigilance)
		{
			eStatus = eSTATUS::Surprised;
			Surprised_Timer = 0;
		}

		ChasePos = sound_source;
	}
}

//壁に当たったらジャンプする判定
bool Enemy::e_wool_jump()
{
	//if ()
	//{
	//	WallTouchFlg = false;
	//	return 1;
	//}
	if (((ePos.x - eAnchor.x - Stage::GetInstance().GetMapChipSize() < Stage::GetInstance().GetLWall(ePos - eAnchor, e_width_size, e_height_size) && eVector == -1) && ePos.x - eAnchor.x - Stage::GetInstance().GetMapChipSize() > Lwall) ||
		((ePos.x + e_width_size - eAnchor.x + Stage::GetInstance().GetMapChipSize() > Stage::GetInstance().GetRWall(ePos - eAnchor, e_width_size, e_height_size) && eVector == 1) && ePos.x + e_width_size - eAnchor.x + Stage::GetInstance().GetMapChipSize() < Rwall))
	{
		return 1;
	}

	return 0;
}

//ジャンプ
void Enemy::jump()
{
	if (jpflg)
	{
		gravity = 180;
		jpflg = 0;
	}
}

//重力
vivid::Vector2 Enemy::Gravity(vivid::Vector2 pos = { 0.0f,0.0f }, float yuka = 600, int CharacterVSize = 32, vivid::Vector2 anchor = { 0.0f,0.0f }, float height = 50, float upspeed = 5, float downspeed = 100)
{
	height /= 57;
	pos.y += sin(gravity * 3.14 / 100) * height * upspeed;
	if (gravity >= 100 - (0.5 * downspeed))
	{
		gravity -= upspeed;
		if (gravity <= 100 - (0.5 * downspeed))
			gravity = 100 - (0.5 * downspeed);
	}
	if (pos.y > yuka - (CharacterVSize - anchor.y))
	{
		pos.y = yuka - (CharacterVSize - anchor.y);
		jpflg = 1;
		//if (WallTouchFlg)
		//{
		//	if (abs( ePos.x - WallTouchPosX) < 3)
		//		eVector *= -1;
		//	WallTouchFlg = false;
		//}
	}
	return pos;
}

void Enemy::player_check(bool shielding)
{
	if (shielding == true)
	{
		Vigilance_Timer = 0;
		eStatus = eSTATUS::Wandering;
	}
	else if (eStatus == eSTATUS::Wandering && shielding == false)
	{
		eStatus = eSTATUS::Surprised;
	}

}
