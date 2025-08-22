#include "enemy.h"
#include "..\..\stage\stage.h"
#include"..\..\item_manager\item_manager.h"

const int Enemy::e_visibility_width_size = 400;
const int Enemy::e_visibility_height_size = 400;

const int Enemy::e_width_size = 128;						//�G�l�~�[�̉��̃h�b�g��
const int Enemy::e_height_size = 98;                       //�G�l�~�[�̏c;;;;�̃h�b�g��

const int Enemy::mark_width_size = 32;		//!�̉��̃h�b�g��
const int Enemy::mark_height_size = 32;      //!�̏c�̃h�b�g��

const float Enemy::eSpeed = 4;						//�G�l�~�[�̏��񒆂̈ړ����x
const float Enemy::eChaseSpeed = 6;					//�G�l�~�[�̃v���C���[�ǐՒ��̈ړ����x
const int Enemy::Source_End_Range = 4;				//�x�����W�Ƃ̂����̍������̐��l���Z���Ȃ�����ǐՂ��I������B
const int Enemy::Vigilance_time = 150;				//�ǐՖڕW�n�_���B��̑ҋ@�t���[����

const int Enemy::Surprised_time = 30;				//�ǐՊJ�n�O�̒�~�t���[����
const float Enemy::enemy_jump_height = 250.0f;		//�W�����v�̍���
const float Enemy::enemy_jump_upspeed = 3.0f;		//�W�����v�̏㏸�X�s�[�h
const float Enemy::enemy_jump_downspeed = 100.0f;	//�����X�s�[�h(�㏸�X�s�[�h�̉�����)

const int Enemy::turn_around_ct = 10;

const int Enemy::animation_change_time = 5;

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
	, Sight_Check_Timer(10)
	, Vigilance_Timer(0)
	, Surprised_Timer(0)
	, eStatus(eSTATUS::Wandering)
	, m_ActiveFlag(true)
	, WallTouchFlg(false)
	, WallTouchPosX(0.0f)
	, AnimationTimer(0)
	, AnimationFrame(0)
	,TurnAroundtimer(10)
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

	enemy_picture_name[(int)eSTATUS::Stop]		= "data\\�G�@\\�w偌^�ҋ@.png";
	enemy_picture_name[(int)eSTATUS::Wandering] = "data\\�G�@\\�w偌^�����s.png";
	enemy_picture_name[(int)eSTATUS::Chase]		= "data\\�G�@\\�w偌^�����s.png";
	enemy_picture_name[(int)eSTATUS::Vigilance] = "data\\�G�@\\�w偌^�ҋ@.png";
	enemy_picture_name[(int)eSTATUS::Surprised] = "data\\�G�@\\�w偌^�ҋ@.png";
	enemy_picture_name[(int)eSTATUS::Kill]		= "data\\�G�@\\�w偌^�����s.png";

	AnimationMaxFrame[(int)eSTATUS::Stop] = 16;
	AnimationMaxFrame[(int)eSTATUS::Wandering] = 8;
	AnimationMaxFrame[(int)eSTATUS::Chase] = 8;
	AnimationMaxFrame[(int)eSTATUS::Vigilance] = 16;
	AnimationMaxFrame[(int)eSTATUS::Surprised] = 16;
	AnimationMaxFrame[(int)eSTATUS::Kill] = 8;
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
	bool flg = false;	
	vivid::Vector2 item;																					//�A�C�e���ƃG�l�~�[�̋����𑪂�̂Ɏg��
	item.x = abs(ItemManager::GetInstance().GetItemPos().x - ePos.x);										//�A�C�e���ƃG�l�~�[�̉��̋���
	item.y = abs(ItemManager::GetInstance().GetItemPos().y - ePos.y);										//�A�C�e���ƃG�l�~�[�̏c�̋���
	if (sqrt((item.x * item.x) + (item.y * item.y)) <= ItemManager::GetInstance().GetEfectiveArea())		//�������ŋ��������ߔ�ׂ�
	{
		flg = true;		//�������G�l�~�[�̍��G�͈͓��ɂ���
	}
	else 
		flg = false;	//�������G�l�~�[�̍��G�͈͊O�ɂ���
	if (ItemManager::GetInstance().GetItemActiveFlag() == true&& flg == true)
	{
		eStatus = eSTATUS::Surprised;
	}

	Sight_Check_Timer++;
	vivid::Vector2 e_Velocity = {0.0f,0.0f};
	switch (eStatus)
	{
	case eSTATUS::Stop:
		break;
	case eSTATUS::Wandering:
		if (eVector == 1)
		{
			e_Velocity.x += eSpeed;
			if (ePos.x+ e_Velocity.x >= Rwall)
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
		if (ItemManager::GetInstance().GetItemActiveFlag()==false)
		{


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
		}
		else
			eStatus = eSTATUS::Vigilance;
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
				if (ItemManager::GetInstance().GetItemActiveFlag() == false)
				eStatus = eSTATUS::Chase;
				else
				{
					eStatus = eSTATUS::Vigilance;
					Vigilance_Timer = 0;
				}
			}
		
		break;
	default:
		break;
	}

	//�n��
	if (ePos.y + e_height_size - eAnchor.y > Stage::GetInstance().GetRoundHeight(ePos, e_width_size, e_height_size))
	{
		ePos.y = Stage::GetInstance().GetRoundHeight(ePos, e_width_size, e_height_size) - e_height_size+eAnchor.y;
	}
	bool TurnAroundFlg=false;
	TurnAroundtimer++;
	//��
	ePos.x += e_Velocity.x;
	if (ePos.x- eAnchor.x < Stage::GetInstance().GetLWall(ePos - eAnchor, e_width_size, e_height_size) && eVector == -1)
	{
		ePos.x = Stage::GetInstance().GetLWall(ePos, e_width_size, e_height_size)- eAnchor.x;
		TurnAroundFlg = true;
	}
	//�E
	if (ePos.x + e_width_size- eAnchor.x > Stage::GetInstance().GetRWall(ePos - eAnchor, e_width_size, e_height_size)&&eVector==1)
	{
		ePos.x = Stage::GetInstance().GetRWall(ePos, e_width_size, e_height_size) - e_width_size+ eAnchor.x;
		TurnAroundFlg = true;
	}
	//�V��
	if (ePos.y- eAnchor.y < Stage::GetInstance().GetCeiling(ePos, e_width_size, e_height_size))
	{
		ePos.y = Stage::GetInstance().GetCeiling(ePos, e_width_size, e_height_size)+ eAnchor.y;
	}
	if (TurnAroundFlg&&TurnAroundtimer>=10)
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
	AnimationTimer++;
	if (AnimationTimer>=animation_change_time)
	{
		AnimationTimer -= animation_change_time;
		++AnimationFrame %= AnimationMaxFrame[(int)eStatus];
	}


	eScale.x = abs(eScale.x) * eVector;

#ifdef _DEBUG
	vivid::DrawTexture("data\\�G���E.png", { ePos.x - e_visibility_width_size / 2 - scroll.x,ePos.y - e_visibility_height_size / 2 - scroll.y }, 0x6fffffff);
#endif // DEBUG



	vivid::Rect eRect;						//�G�l�~�[�̉摜�͈�

	eRect.top = 0;
	eRect.bottom = e_height_size ;
	eRect.left = (AnimationFrame % AnimationMaxFrame[(int)eStatus]) * e_width_size;
	eRect.right = eRect.left + e_width_size;

	vivid::DrawTexture(enemy_picture_name[(int)eStatus], {ePos.x - (e_width_size / 2) - scroll.x,ePos.y - (e_height_size / 2) - scroll.y}, 0xffffffff, eRect, eAnchor, eScale);
	if (eStatus == eSTATUS::Surprised)
	{
		vivid::Rect markRect = { 0,0,mark_height_size,mark_width_size };						//!�̉摜�͈�
		markPos = { ePos.x - (mark_width_size / 2),(ePos.y - eAnchor.y - mark_height_size - (eScale.y * e_height_size / 10)) };
		markScale = { abs(eScale.x) ,abs(eScale.y) };
		vivid::DrawTexture("data\\exclamation_mark.png", markPos - scroll, 0xffffffff, markRect, markAnchor, markScale);
	}
	if (eStatus == eSTATUS::Vigilance)
	{
		vivid::Rect markRect = { 0,0,mark_height_size,mark_width_size };						//?�̉摜�͈�
		markPos = { ePos.x - (mark_width_size / 2),(ePos.y - eAnchor.y - mark_height_size - (eScale.y * e_height_size / 10)) };
		markScale = { abs(eScale.x) ,abs(eScale.y) };
		vivid::DrawTexture("data\\question_mark.png", markPos - scroll, 0xffffffff, markRect, markAnchor, markScale);
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
	//if ()
	//{
	//	WallTouchFlg = false;
	//	return 1;
	//}
	if (((ePos.x - eAnchor.x -Stage::GetInstance().GetMapChipSize() < Stage::GetInstance().GetLWall(ePos - eAnchor, e_width_size, e_height_size) && eVector == -1)&& ePos.x - eAnchor.x - Stage::GetInstance().GetMapChipSize()>Lwall)||
		((ePos.x + e_width_size - eAnchor.x + Stage::GetInstance().GetMapChipSize() > Stage::GetInstance().GetRWall(ePos - eAnchor, e_width_size, e_height_size) && eVector == 1)&& ePos.x + e_width_size - eAnchor.x + Stage::GetInstance().GetMapChipSize()<Rwall))
	{
		return 1;
	}

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
	if(shielding==true)
	{
		Vigilance_Timer = 0;
		eStatus = eSTATUS::Wandering;
	}
	else if (eStatus == eSTATUS::Wandering && shielding == false)
	{
		eStatus = eSTATUS::Surprised;
	}
	
}
