#include "timer.h"

Timer::Timer(void)
	: max_timer(300)
	, one_second_flame(60)
{
}

void Timer::Initialize(void)
{
	flame_timer = max_timer * one_second_flame;
}

void Timer::Update(void)
{
	ChangeTimer();
}

void Timer::Draw(void)
{
}

void Timer::Finalize(void)
{
}

void Timer::ChangeTimer(void)
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
		}
		flame_timer--;
	}
}
