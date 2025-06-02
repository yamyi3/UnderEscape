#include "enemy.h"

Enemy::Enemy(void)
	: ePos(300.0f, 500.0f)
	, eCircleRadius(200.0f)
{
}
void Enemy::Initialize(vivid::Vector2 pos, float L, float R, float vector, float ground)
{
	eGround = ground;
	if (L == R)
		eStatus = eSTATUS::Stop;
	if (L > R)
	{
		Initialize(pos, R, L, vector,ground);
	}
	else
	{
		ePos = pos;
		eGround = ground;
		Rwool = R;
		Lwool = L;
		eVector = vector;
		gravity = 100;
		jpflg = 0;
		eCircleCenterPos.x = ePos.x-e_width_size/2/* + eCircleRadius*/;
		eCircleCenterPos.y = ePos.y-e_height_size/2/* + eCircleRadius*/;
	}
}

void Enemy::Initialize(vivid::Vector2 pos, float L, float R, float vector)
{
	Initialize(pos, L, R, vector,600.0f);
}

void Enemy::Initialize(vivid::Vector2 pos, float L, float R)
{
	Initialize(pos, L, R, 1,600.0f);
}
void Enemy::Initialize(void)
{
	Enemy::Initialize({ 300.0f, 500.0f },300.0f,600.0f);
}

void Enemy::Update(void)
{
	switch (eStatus)
	{
	case eSTATUS::Stop:
		break;
	case eSTATUS::Wandering:
		if (eVector == 1)
		{
			ePos.x += eSpeed;
			if (ePos.x >= Rwool)
			{
				eVector *= -1;
				if (Lwool == Rwool)
					eStatus = eSTATUS::Stop;
			}
		}
		else
		{
			ePos.x -= eSpeed;
			if (ePos.x <= Lwool)
			{
				eVector *= -1;
				if (Lwool == Rwool)
					eStatus = eSTATUS::Stop;
			}
		}
		break;
	case eSTATUS::Chase:
		if (ChasePos.x > ePos.x)
		{
			ePos.x += eChaseSpeed;
			eVector = 1;
		}
		else
		{
			ePos.x -= eChaseSpeed;
			eVector = -1;
		}
		if (abs(ChasePos.x - ePos.x) < Source_End_Range)
		{
			Vigilance_Timer = 0;
			eStatus = eSTATUS::Vigilance;
		}
		break;
	case eSTATUS::Vigilance:
		if (++Vigilance_Timer >= Vigilance_time)
		{
			if (Lwool == Rwool)
				eStatus = eSTATUS::Stop;
			else
				eStatus = eSTATUS::Wandering;
		}
		break;
	case eSTATUS::Surprised:
		if (++Surprised_Timer >= Surprised_time)
		{
			eStatus = eSTATUS::Chase;
		}
		break;
	default:
		break;
	}
	if (e_wool_jump())
	{
		jump();
	}
	ePos = Gravity(ePos, eGround, e_height_size, eAnchor, enemy_jump_height, enemy_jump_upspeed, enemy_jump_downspeed);

	eCircleCenterPos.x = ePos.x - e_width_size / 2/* + eCircleRadius*/;
	eCircleCenterPos.y = ePos.y - e_height_size / 2/* + eCircleRadius*/;
}

void Enemy::Draw(void)
{
	eScale.x = abs(eScale.x) * eVector;
	vivid::DrawTexture("data\\敵視界.png", { ePos.x - e_visibility_width_size / 2,ePos.y - e_visibility_height_size / 2 },0x6fffffff);

	vivid::DrawTexture("data\\abe.png", { ePos.x - (e_width_size / 2),ePos.y-(e_height_size/2)}, 0xffffffff, eRect, eAnchor, eScale);
	if (eStatus == eSTATUS::Surprised)
	{
		exclamationPos = { ePos.x,(ePos.y - eAnchor.y) - ((exclamation_height_size - exclamationAnchor.y) - (e_height_size / 5)) * (eScale.y) };
		exclamationScale = { abs(eScale.x) ,abs(eScale.y) };
		vivid::DrawTexture("data\\ball.png", { exclamationPos.x - (exclamation_width_size / 2),exclamationPos.y }, 0xffffffff, exclamationRect, exclamationAnchor, exclamationScale);
	}

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
	//仮置きでFジャンプ
	if (vivid::keyboard::Trigger(vivid::keyboard::KEY_ID::F))
		return 1;

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
	}
	return pos;
}