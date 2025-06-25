#include "stage.h"
#include "../character/character.h"

const float Stage::wall_width = 200.0f;
const float Stage::wall_height = 200.0f;
unsigned int Stage::wall_color = 0xff000000;
const float	Stage::ground_line = (vivid::WINDOW_HEIGHT - 300.0f);

const float	Stage::walk_speed = Character::GetInstance().GetWalk();
const float	Stage::dash_speed = Character::GetInstance().GetDash();
const float	Stage::sneak_speed = Character::GetInstance().GetSneak();

const float Stage::round_width = vivid::WINDOW_WIDTH;

vivid::Vector2 Stage::start_pos = { 0.0f, vivid::WINDOW_HEIGHT - 300.0f };
vivid::Vector2 Stage::goal_pos = { Stage::round_width * 3 , vivid::WINDOW_HEIGHT - 300.0f };

Stage& Stage::GetInstance(void)
{
	static Stage	instance;
	return instance;
}

void Stage::Initialize(void)
{
	max_round = 3;
	int n = 0;
	for (int i = 0; i < max_round; i++)
	{
		round_pos[i].x = n;
		n += round_width;
		round_pos[i].y = vivid::WINDOW_HEIGHT - 300.0f;
	}
	wall_pos.y = round_pos[0].y - wall_height;
	wall_pos.x = 400;

	WallManager::GetInstance().GenerateWall(wall_pos,wall_height,wall_width,wall_color);
	sc_speed = walk_speed;
}

void Stage::Update(void)
{
	WallManager::GetInstance().Update();
	WallManager::GetInstance().Input_scroll(round_pos[0].x);
}

void Stage::Draw(void)
{
	for (int i = 0; i < max_round; i++)
	{
		vivid::DrawTexture("data\\round_box.png", round_pos[i]);
	}
	WallManager::GetInstance().Draw();
}

void Stage::Finalize(void)
{
}

void Stage::ScrollStage(void)
{
	//keyboardネームスペースの宣言
	namespace keyboard = vivid::keyboard;

	//通常時はスクロール速度が通常速度になる
	sc_speed = walk_speed;
	//左SHIFTを押している間はスクロール速度がダッシュ速度になる
	if (keyboard::Button(keyboard::KEY_ID::LSHIFT))
	{
		sc_speed = dash_speed;
	}
	//左CTRLを押している間はスクロール速度が歩行速度になる
	if (keyboard::Button(keyboard::KEY_ID::LCONTROL))
	{
		sc_speed = sneak_speed;
	}

	//左方向へのスクロール処理
	if (keyboard::Button(keyboard::KEY_ID::A))
	{
		//背景のスクロールの処理
		for (int i = 0; i < max_round; i++)
		{
			round_pos[i].x = round_pos[i].x + sc_speed;
			if (round_pos[i].x > round_width)
			{
				round_pos[i].x = -round_width - (round_width - round_pos[i].x);
			}
		}
	}
	//右方向へのスクロール処理
	if (keyboard::Button(keyboard::KEY_ID::D))
	{
		//背景の右スクロール処理
		for (int i = 0; i < max_round; i++)
		{
			round_pos[i].x = round_pos[i].x - sc_speed;
			if (round_pos[i].x < -round_width) {
				round_pos[i].x = round_width - (-round_width - round_pos[i].x);
			}
		}
	}
}
