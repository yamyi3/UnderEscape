#include "stage.h"
#include "../character/character.h"

const float Stage::wall_width = 200.0f;
const float Stage::wall_height = 200.0f;
unsigned int Stage::wall_color = 0xff000000;

const float	Stage::run_speed = Character::GetInstance().GetRun();
const float	Stage::dash_speed = Character::GetInstance().GetDash();
const float	Stage::walk_speed = Character::GetInstance().GetWalk();

Stage& Stage::GetInstance(void)
{
	static Stage	instance;
	return instance;
}

void Stage::Initialize(void)
{
	int n = 0;
	for (int i = 0; i < max_round; i++)
	{
		round_pos[i].x = n;
		n += round_width;
		round_pos[i].y = (float)vivid::WINDOW_HEIGHT - 300;
	}
	wall_pos.y = round_pos[0].y - wall_height;
	wall_pos.x = 400;
	sc_speed = run_speed;
	max_round = 3;
	round_width = vivid::WINDOW_WIDTH;
}

void Stage::Update(void)
{
}

void Stage::Draw(void)
{
	for (int i = 0; i < max_round; i++)
	{
		vivid::DrawTexture("data\\round_box.png", round_pos[i]);
	}
	vivid::DrawTexture("data\\�Օ�.png", wall_pos, wall_color);
}

void Stage::Finalize(void)
{
}

void Stage::ScrollStage(void)
{
	//keyboard�l�[���X�y�[�X�̐錾
	namespace keyboard = vivid::keyboard;

	//�ʏ펞�̓X�N���[�����x���ʏ푬�x�ɂȂ�
	sc_speed = run_speed;
	//��SHIFT�������Ă���Ԃ̓X�N���[�����x���_�b�V�����x�ɂȂ�
	if (keyboard::Button(keyboard::KEY_ID::LSHIFT))
	{
		sc_speed = dash_speed;
	}
	//��CTRL�������Ă���Ԃ̓X�N���[�����x�����s���x�ɂȂ�
	if (keyboard::Button(keyboard::KEY_ID::LCONTROL))
	{
		sc_speed = walk_speed;
	}

	//�������ւ̃X�N���[������
	if (keyboard::Button(keyboard::KEY_ID::A))
	{
		//�w�i�̃X�N���[���̏���
		for (int i = 0; i < max_round; i++)
		{
			round_pos[i].x = round_pos[i].x + sc_speed;
			if (round_pos[i].x > round_width)
			{
				round_pos[i].x = -round_width - (round_width - round_pos[i].x);
			}
		}
	}
	//�E�����ւ̃X�N���[������
	if (keyboard::Button(keyboard::KEY_ID::D))
	{
		//�w�i�̉E�X�N���[������
		for (int i = 0; i < max_round; i++)
		{
			round_pos[i].x = round_pos[i].x - sc_speed;
			if (round_pos[i].x < -round_width) {
				round_pos[i].x = round_width - (-round_width - round_pos[i].x);
			}
		}
	}
}
