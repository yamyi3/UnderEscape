#include "enemy.h"

const int Enemy::e_visibility_width_size = 400;
const int Enemy::e_visibility_height_size = 400;

const int Enemy::e_width_size = 64;						//�G�l�~�[�̉��̃h�b�g��
const int Enemy::e_height_size = 64;                       //�G�l�~�[�̏c;;;;�̃h�b�g��

const int Enemy::mark_width_size = 32;		//!�̉��̃h�b�g��
const int Enemy::mark_height_size = 32;      //!�̏c�̃h�b�g��

const float Enemy::eSpeed = 4;						//�G�l�~�[�̏��񒆂̈ړ����x
const float Enemy::eChaseSpeed = 6;					//�G�l�~�[�̃v���C���[�ǐՒ��̈ړ����x
const int Enemy::Source_End_Range = 4;				//�x�����W�Ƃ̂����̍������̐��l���Z���Ȃ�����ǐՂ��I������B
const int Enemy::Vigilance_time = 150;				//�ǐՖڕW�n�_���B��̑ҋ@�t���[����

const int Enemy::Surprised_time = 30;				//�ǐՊJ�n�O�̒�~�t���[����
const float Enemy::enemy_jump_height = 150.0f;		//�W�����v�̍���
const float Enemy::enemy_jump_upspeed = 3.0f;		//�W�����v�̏㏸�X�s�[�h
const float Enemy::enemy_jump_downspeed = 100.0f;	//�����X�s�[�h(�㏸�X�s�[�h�̉�����)

const float Enemy::eCircleRadius = 200.0f;

Enemy::Enemy(void)
	: ePos(300.0f, 500.0f)
	, eAnchor(e_width_size / 2.0f, e_height_size / 2.0f)
	, eScale(1.0f, 1.0f)
	, markPos(0.0f, 0.0f)
	, markAnchor(mark_width_size / 2.0f, mark_height_size / 2.0f)
	, markScale(1.0, 1.0)
	, gravity(100)
	, eGround(600.0f)
	, eVector(1)
	, Vigilance_Timer(0)
	, Surprised_Timer(0)
	, eStatus(eSTATUS::Wandering)
	, m_ActiveFlag(true)
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
		Rwool = R;
		Lwool = L;
		eVector = vector;
		gravity = 100;
		jpflg = 0;
		eCircleCenterPos.x = ePos.x - e_width_size / 2;
		eCircleCenterPos.y = ePos.y - e_height_size / 2;
	}
}

void Enemy::Initialize(vivid::Vector2 pos, float L, float R, float vector)
{
	Initialize(pos, L, R, vector, 600.0f);
}

void Enemy::Initialize(vivid::Vector2 pos, float L, float R)
{
	Initialize(pos, L, R, 1, 600.0f);
}
void Enemy::Initialize(vivid::Vector2 pos)
{
	Initialize(pos, pos.x, pos.x, 1, 600.0f);
}
void Enemy::Initialize(void)
{
	Enemy::Initialize({ 300.0f, 500.0f }, 300.0f, 600.0f);
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

#ifdef _DEBUG
	vivid::DrawTexture("data\\�G���E.png", { ePos.x - e_visibility_width_size / 2,ePos.y - e_visibility_height_size / 2 }, 0x6fffffff);
#endif // DEBUG



	vivid::Rect eRect = { 0,0,e_height_size,e_width_size };						//�G�l�~�[�̉摜�͈�

	vivid::DrawTexture("data\\abe.png", { ePos.x - (e_width_size / 2),ePos.y - (e_height_size / 2) }, 0xffffffff, eRect, eAnchor, eScale);
	if (eStatus == eSTATUS::Surprised)
	{
		vivid::Rect markRect = { 0,0,mark_height_size,mark_width_size };						//!�̉摜�͈�
		markPos = { ePos.x - (mark_width_size / 2),(ePos.y - eAnchor.y - mark_height_size - (eScale.y * e_height_size / 10)) };
		markScale = { abs(eScale.x) ,abs(eScale.y) };
		vivid::DrawTexture("data\\exclamation_mark.png", { markPos.x,markPos.y }, 0xffffffff, markRect, markAnchor, markScale);
	}
	if (eStatus == eSTATUS::Vigilance)
	{
		vivid::Rect markRect = { 0,0,mark_height_size,mark_width_size };						//?�̉摜�͈�
		markPos = { ePos.x - (mark_width_size / 2),(ePos.y - eAnchor.y - mark_height_size - (eScale.y * e_height_size / 10)) };
		markScale = { abs(eScale.x) ,abs(eScale.y) };
		vivid::DrawTexture("data\\question_mark.png", { markPos.x,markPos.y }, 0xffffffff, markRect, markAnchor, markScale);
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

bool Enemy::CheckHitPlayer(const vivid::Vector2& cPos, int c_height, int c_width)
{
	//�_�Ƌ�`�̔��肻��1(����)
	bool result_h = ePos.x > cPos.x - eCircleRadius
		&& ePos.x < cPos.x + c_width + eCircleRadius
		&& ePos.y > cPos.y
		&& ePos.y < cPos.y + c_height;

	//�_�Ƌ�`�̔��肻��2(�c��)
	bool result_v = ePos.x > cPos.x
		&& ePos.x < cPos.x + c_width
		&& ePos.y > cPos.y - eCircleRadius
		&& ePos.y < cPos.y + c_height + eCircleRadius;

	//�_�Ɖ~�̔���	
	//���@�̍���(LeftUpper)
	vivid::Vector2 v = ePos - cPos;
	bool result_lu = v.Length() <= eCircleRadius;
	//���@�̉E��(RightUpper)
	v = ePos - vivid::Vector2(cPos.x + c_width, cPos.y);
	bool result_ru = v.Length() <= eCircleRadius;
	//���@�̍���(LeftDown)
	v = ePos - vivid::Vector2(cPos.x, cPos.y + c_height);
	bool result_ld = v.Length() <= eCircleRadius;
	//���@�̉E��(RightDown)
	v = ePos - vivid::Vector2(cPos.x + c_width, cPos.y + c_height);
	bool result_rd = v.Length() <= eCircleRadius;
	//��L�̔��肩�瓖�����Ă��邩(���E�ɓ����Ă��邩)�𔻒f����
	if (result_h || result_v || result_lu || result_ru || result_ld || result_rd)
	{
		return true;
	}
	//�������Ă��Ȃ��ꍇ��false��Ԃ�
	else
	{
		return false;
	}
}

//���̔���
void Enemy::sound_sensor(vivid::Vector2 sound_source, float sound_size)
{
	float sound_work = 1.0f;														//���̑傫���̔{��
	vivid::Vector2 work;															//�����ƃG�l�~�[�̋����𑪂�̂Ɏg��
	work.x = abs(sound_source.x - ePos.x);										//�����ƃG�l�~�[�̉��̋���
	work.y = abs(sound_source.y - ePos.y);										//�����ƃG�l�~�[�̏c�̋���
	if (sqrt((work.x * work.x) + (work.y * work.y)) <= sound_size * sound_work)		//�������ŋ��������ߔ�ׂ�
	{
		if (eStatus == eSTATUS::Wandering || eStatus == eSTATUS::Vigilance)
		{
			eStatus = eSTATUS::Surprised;
			Surprised_Timer = 0;
		}

		ChasePos = sound_source;
	}
}

//�ǂɓ���������W�����v���锻��
bool Enemy::e_wool_jump()
{
	//���u����F�W�����v
	/*if (vivid::keyboard::Trigger(vivid::keyboard::KEY_ID::F))
		return 1;*/

	return 0;
}

//�W�����v
void Enemy::jump()
{
	if (jpflg)
	{
		gravity = 180;
		jpflg = 0;
	}
}

//�d��
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