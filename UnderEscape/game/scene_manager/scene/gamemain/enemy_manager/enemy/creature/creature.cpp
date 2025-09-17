#include "creature.h"



const int Creature::e_visibility_width_size = 400;
const int Creature::e_visibility_height_size = 400;

const int    Creature::m_width = 301;            //!< 幅 
const int    Creature::m_height = 190;           //!< 高さ 	
const float	 Creature::m_circle_radius = 300.0f;    //視界範囲
const float  Creature::m_move_speed = 3;       //!< 移動速度 
const float  Creature::m_chase_move_speed = 9;       //!< 移動速度 
const float  Creature::m_jump_height = 250.0f;
const float  Creature::m_jump_upspeed = 3.0f;
const float  Creature::m_jump_downspeed = 100.0f;
const bool   Creature::viewing_angle = 1;
Creature::Creature(void)
	:Enemy(m_width, m_height, m_move_speed, m_chase_move_speed, m_jump_height, m_jump_upspeed, m_jump_downspeed, m_circle_radius, viewing_angle)
{
}

Creature::~Creature(void)
{
}

void Creature::Initialize(vivid::Vector2 pos, float L, float R, float vector, float ground)
{
	Enemy::Initialize(pos, L, R, vector, ground);
	AnimationMaxFrame[(int)eSTATUS::Stop] = 8;
	AnimationMaxFrame[(int)eSTATUS::Wandering] = 10;
	AnimationMaxFrame[(int)eSTATUS::Chase] = 7;
	AnimationMaxFrame[(int)eSTATUS::Vigilance] = 8;
	AnimationMaxFrame[(int)eSTATUS::Surprised] = 8;
	AnimationMaxFrame[(int)eSTATUS::Kill] = 6;
}

void Creature::Initialize(vivid::Vector2 pos, float L, float R, float vector)
{
	Initialize(pos, L, R, vector, 60000.0f);
}

void Creature::Initialize(vivid::Vector2 pos, float L, float R)
{
	Initialize(pos, L, R, 1, 60000.0f);
}

void Creature::Initialize(vivid::Vector2 pos)
{
	Initialize(pos, pos.x, pos.x, 1, 60000.0f);
}

void Creature::Initialize(void)
{
	Initialize({ 300.0f, 500.0f }, 300.0f, 60000.0f);
}

void Creature::Draw(vivid::Vector2 scroll)
{
	AnimationTimer++;
	if (AnimationTimer >= animation_change_time)
	{
		AnimationTimer -= animation_change_time;
		++AnimationFrame %= AnimationMaxFrame[(int)eStatus];
	}


	eScale.x = abs(eScale.x) * eVector;

#ifdef _DEBUG
	vivid::DrawTexture(enemy_sight, { ePos.x - e_visibility_width_size / 2 - scroll.x,ePos.y - e_visibility_height_size / 2 - scroll.y }, 0x6fffffff);
#endif // DEBUG



	vivid::Rect eRect;						//エネミーの画像範囲

	eRect.top = 0;
	eRect.bottom = e_height_size;
	eRect.left = (AnimationFrame % AnimationMaxFrame[(int)eStatus]) * e_width_size;
	eRect.right = eRect.left + e_width_size;

	vivid::DrawTexture(enemy_picture_name[(int)eStatus], { ePos.x - eAnchor.x - scroll.x,ePos.y - eAnchor.y - scroll.y }, 0xffffffff, eRect, eAnchor, eScale);
	if (eStatus == eSTATUS::Surprised)
	{
		vivid::Rect markRect = { 0,0,mark_height_size,mark_width_size };						//!の画像範囲
		markPos = { ePos.x - (mark_width_size / 2),(ePos.y - eAnchor.y - mark_height_size - (eScale.y * e_height_size / 10)) };
		markScale = { abs(eScale.x) ,abs(eScale.y) };
		vivid::DrawTexture("data\\exclamation_mark.png", markPos - scroll, 0xffffffff, markRect, markAnchor, markScale);
	}
	if (eStatus == eSTATUS::Vigilance)
	{
		vivid::Rect markRect = { 0,0,mark_height_size,mark_width_size };						//?の画像範囲
		markPos = { ePos.x - (mark_width_size / 2),(ePos.y - eAnchor.y - mark_height_size - (eScale.y * e_height_size / 10)) };
		markScale = { abs(eScale.x) ,abs(eScale.y) };
		vivid::DrawTexture("data\\question_mark.png", markPos - scroll, 0xffffffff, markRect, markAnchor, markScale);
	}
}
