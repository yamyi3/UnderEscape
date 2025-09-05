#include "spider_robo.h"
const int    SpiderRobo::m_width = 128;            //!< 幅 
const int    SpiderRobo::m_height = 98;           //!< 高さ 	
const float	 SpiderRobo::m_circle_radius = 200.0f;    //視界範囲
const float  SpiderRobo::m_move_speed = 4;       //!< 移動速度 
const float  SpiderRobo::m_chase_move_speed = 6;       //!< 移動速度 
const float  SpiderRobo::m_jump_height = 250.0f;
const float  SpiderRobo::m_jump_upspeed = 3.0f;
const float  SpiderRobo::m_jump_downspeed = 100.0f;
SpiderRobo::SpiderRobo(void)
	:Enemy(m_width,m_height,m_move_speed,m_chase_move_speed,m_jump_height,m_jump_upspeed,m_jump_downspeed,m_circle_radius)
{
}

SpiderRobo::~SpiderRobo(void)
{
}

void SpiderRobo::Initialize(vivid::Vector2 pos, float L, float R, float vector, float ground)
{
	Enemy::Initialize(pos, L, R, vector, ground);
	AnimationMaxFrame[(int)eSTATUS::Stop] = 16;
	AnimationMaxFrame[(int)eSTATUS::Wandering] = 8;
	AnimationMaxFrame[(int)eSTATUS::Chase] = 8;
	AnimationMaxFrame[(int)eSTATUS::Vigilance] = 16;
	AnimationMaxFrame[(int)eSTATUS::Surprised] = 16;
	AnimationMaxFrame[(int)eSTATUS::Kill] = 8;
}

void SpiderRobo::Initialize(vivid::Vector2 pos, float L, float R, float vector)
{
	Initialize(pos, L, R, vector, 60000.0f);
}

void SpiderRobo::Initialize(vivid::Vector2 pos, float L, float R)
{
	Initialize(pos, L, R, 1, 60000.0f);
}

void SpiderRobo::Initialize(vivid::Vector2 pos)
{
	Initialize(pos, pos.x, pos.x, 1, 60000.0f);
}

void SpiderRobo::Initialize(void)
{
	Initialize({ 300.0f, 500.0f }, 300.0f, 60000.0f);
}

void SpiderRobo::Draw(vivid::Vector2 scroll)
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

	vivid::DrawTexture(enemy_picture_name[(int)eStatus], { ePos.x - (e_width_size / 2) - scroll.x,ePos.y - (e_height_size / 2) - scroll.y }, 0xffffffff, eRect, eAnchor, eScale);
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
