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
	vivid::DrawText(40, std::to_string(m_SecondTimer), m_TimerPosition, 0xff00ffff);
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