#include "timer.h"

const int CTimer::one_second_flame = 60;


CTimer& CTimer::GetInstance(void)
{
	static CTimer instance;

	return instance;
}

void CTimer::Initialize(void)
{
	flame_timer = max_timer * one_second_flame;
	m_SecondTimer = max_timer;
}

void CTimer::Update(void)
{
	ChangeTimer();
}

void CTimer::Draw(void)
{
	//100の位の表示範囲
	vivid::Rect h_rect;
	h_rect.left = m_SecondTimer / 100 * 40;
	h_rect.right = h_rect.left + 40;
	h_rect.top = 0;
	h_rect.bottom = h_rect.top + 60;
	//10の位の表示範囲
	vivid::Rect t_rect;
	t_rect.left = (m_SecondTimer % 100) / 10 * 40;
	t_rect.right = t_rect.left + 40;
	t_rect.top = 0;
	t_rect.bottom = t_rect.top + 60;
	//1の位の表示範囲
	vivid::Rect o_rect;
	o_rect.left = ((m_SecondTimer % 100) % 10) * 40;
	o_rect.right = o_rect.left + 40;
	o_rect.top = 0;
	o_rect.bottom = o_rect.top + 60;

	/*vivid::DrawText(40, std::to_string(m_SecondTimer), m_TimerPosition, 0xff00ffff);*/
	if (m_SecondTimer >= 100)
	{
		vivid::DrawTexture("data\\タイマー\\通常フレーム.png", m_TimerPosition + vivid::Vector2(-80.0f, -35.0f), 0xffffffff);
	}
	else
	{
		vivid::DrawTexture("data\\タイマー\\危険フレーム.png", m_TimerPosition + vivid::Vector2(-80.0f, -35.0f), 0xffffffff);
	}
	vivid::DrawTexture("data\\タイマー\\数字.png", m_TimerPosition + vivid::Vector2(10.0f, 10.0f), 0xffffffff, h_rect);
	vivid::DrawTexture("data\\タイマー\\数字.png", m_TimerPosition + vivid::Vector2(50.0f, 10.0f), 0xffffffff, t_rect);
	vivid::DrawTexture("data\\タイマー\\数字.png", m_TimerPosition + vivid::Vector2(90.0f, 10.0f), 0xffffffff, o_rect);
}

void CTimer::Finalize(void)
{
}

void CTimer::ChangeTimer(void)
{
	if (flame_timer >= 0)
	{
		if (flame_timer % one_second_flame == 0)
		{
			int tmp = flame_timer;
			hundred_cnt = tmp / (one_second_flame * 100);
			tmp %= one_second_flame * 100;
			ten_cnt = tmp / (one_second_flame * 10);
			tmp %= one_second_flame * 10;
			one_cnt = tmp / one_second_flame;

			m_SecondTimer = (hundred_cnt * 100) + (ten_cnt * 10) + (one_cnt);
		}
		flame_timer--;
	}
}

int CTimer::GetTimer(void)
{
	return flame_timer;
}

CTimer::CTimer(void)
	: max_timer(300)
	, m_TimerPosition(vivid::Vector2((float)(vivid::WINDOW_WIDTH - 300),(float)100))
	, m_SecondTimer(0)
{
}

CTimer::CTimer(const CTimer& rhs)
{
	(void)rhs;
}

CTimer& CTimer::operator = (const CTimer& rhs)
{
	(void)rhs;

	return *this;
}