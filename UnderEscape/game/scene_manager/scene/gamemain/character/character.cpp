//character.cpp
#include "character.h"
#include "../stage/stage.h"

float	Character::ch_speed = sneak_speed;
unsigned Character::color = 0xffffffff;
bool	Character::m_LandingFlag = false;
bool	Character::cCatch = false;
bool	Character::cAlive = true;
CHARA_SKILL chara_skill = CHARA_SKILL::NORMAL;

const float Character::ch_width		 = 72.0f;			//���@�̕�
const float Character::ch_height	 = 180.0f;			//���@�̍���
const float Character::walk_speed	 = 1.2f;			//���@�̒ʏ�ړ����x
const float Character::dash_speed	 = 2.4f;			//���@�̃_�b�V�����̈ړ����x
const float Character::sneak_speed	 = 0.6f;			//���@�̕��s���̈ړ����x
const float Character::fatigue_speed = 0.3f;			//���@�̔�J���̈ړ����x

int			Character::skill_memory			= 1;
const int	Character::skill_cool_time		= 300;		//�X�L���̃N�[���^�C���̍ő吔(60�t���[�����Z5�b)
const int	Character::activation_time		= 300;		//�X�L���̌��ʎ���(60�t���[�����Z5�b)
const int	Character::stamina_width		= 76;		//�X�^�~�i���݂�1������̕�
const int	Character::stamina_height		= 16;		//�X�^�~�i�Q�[�W�̍���
const int	Character::c_max_stamina		= 5;		//���@�̃X�^�~�i�̍ő�l
int			Character::c_stamina_gauge		= 5;		//���@�̃X�^�~�i�̃Q�[�W
int			Character::c_stamina_count		= 0;		//�X�^�~�i�̌������x��}��J�E���^
int			Character::c_limit_recovery		= 0;		//��J��Ԃ̃X�^�~�i�񕜂܂ł̃J�E���^
int			Character::c_stamina_recovery	= 0;		//�X�^�~�i�񕜂̃J�E���^
bool		Character::c_stamina_dash		= true;		//�_�b�V���\�����ʂ���t���O
bool		Character::c_stamina_fatigue	= false;	//���@����J��Ԃ����ʂ���t���O
const int	Character::c_draw_stamina		= 60;		//�X�^�~�i�̕`�悷��ő�b��(60�t���[�����Z1�b)
bool		Character::c_stamina_draw		= false;	//�X�^�~�i�̕`���؂�ւ���t���O
bool		Character::found_flag			= true;		//����������Ԃ����f����t���O(���������Ɏg�p)

const float Character::scroll_width_space = 850;
const float Character::scroll_height_space = 300;

Character& Character::GetInstance(void)
{
	static Character	instance;
	return instance;
}

//������
void Character::Initialize(vivid::Vector2 rPos)
{
	accelerator = vivid::Vector2::ZERO;
	cPos = {100.0f, rPos.y - ch_height};
	chara_state = CHARA_STATE::WAIT;

	c_anchor	= {ch_width / 2,ch_height / 2 };
	c_scale		= {  1.0f,1.0f };
	c_rotate	= 0.0f;

	c_anime_frame = 0;
	c_anime_timer = 0;
	c_change_anime_timer = 6;
	c_change_anime_frame = 0;

	stamina_anchor = { ((float)stamina_width / 2.0f), ((float)stamina_height / 2.0f) };
	stamina_scale = { 1.0f, 1.0f };

	skill_active_flag = false;
	skill_cool_flag = false;
	active_count = 0;
	cool_time_count = 0;
	c_stamina_draw_count = 0;

	Scroll = { 0.0f, 0.0f };
}

void Character::Update(void)
{
	//���@�̃L�[�{�[�h����
	//KeyboardControl();
	//���@�̃R���g���[���[����
	ControllerControl();
	//��ʒ[�̔���
	CheckWindow();
	//�N�[���^�C���̏���
	CoolTime();
	//�X�e�[�W�Ƃ̓����蔻��
	StageHit();
	//�A�j���[�V�����̍X�V
	UpdateAnimation();
	//�X�N���[���̍X�V
	Scroll_Update();
	//�X�^�~�i�̕`��؂�ւ�
	StaminaDraw();
}

//�`��
void Character::Draw(void)
{
	//->�X�^�~�i�̕`����W�̍X�V
	stamina_pos.x = (float)(((cPos.x + (ch_width / 2.0f))- (stamina_width / 2.0f)));
	stamina_pos.y = (float)(cPos.y - 20);
	//<-�X�^�~�i�̕`����W�̍X�V

	//->���@��rect�X�V
	c_rect.top = 0;
	c_rect.bottom = ch_height;
	c_rect.left = ch_width * (c_anime_frame % c_change_anime_frame);
	c_rect.right = c_rect.left + ch_width;
	//<-���@��rect�X�V
	
	//->�X�^�~�i��rect�X�V
	stamina_rect.top = 0;
	stamina_rect.bottom = stamina_height;
	if (c_stamina_dash == true)
	{
		stamina_rect.left = stamina_width * (5 - c_stamina_gauge);
	}
	if (c_stamina_dash == false)
	{
		stamina_rect.left = stamina_width * c_stamina_gauge;
	}
	stamina_rect.right = stamina_rect.left + stamina_width;
	//<-�X�^�~�i��rect�X�V

	//���@�̕`��
	vivid::DrawTexture(c_image[(int)chara_skill][(int)chara_state], cPos - Scroll, color, c_rect, c_anchor, c_scale);
	//�X�^�~�i�`��t���O��true�̎��ɂ̂݃X�^�~�i�Q�[�W��`�悷��
	if (c_stamina_draw)
		vivid::DrawTexture(c_dash_image[c_stamina_dash], stamina_pos - Scroll, 0xffffffff, stamina_rect, stamina_anchor, stamina_scale);

	//�f�o�b�O���[�h�̎��Ɋe�K�v����\��
#ifdef _DEBUG
	switch (chara_skill)
	{
	case CHARA_SKILL::NORMAL:
		vivid::DrawText(40, "�ӂ�����[", vivid::Vector2(0.0f, 0.0f), 0xff00ffff);
		break;
	case CHARA_SKILL::ANIMALLEG:
		vivid::DrawText(40, "�����̂���[", vivid::Vector2(0.0f, 0.0f), 0xff00ffff);
		break;
	case CHARA_SKILL::INVISIBLE:
		vivid::DrawText(40, "�݂��Ȃ���[", vivid::Vector2(0.0f, 0.0f), 0xff00ffff);
		break;
	}
	if (skill_active_flag == false)
		vivid::DrawText(40, "����������ĂȂ���[", vivid::Vector2(0.0f, 50.0f), 0xff00ffff);
	if (skill_active_flag)
		vivid::DrawText(40, "�����������[", vivid::Vector2(0.0f, 50.0f), 0xff00ffff);
	if (skill_memory == (int)CHARA_SKILL::ANIMALLEG)
		vivid::DrawText(40, "�����悢��[", vivid::Vector2(0.0f, 100.0f), 0xff00ffff);
	if (skill_memory == (int)CHARA_SKILL::INVISIBLE)
		vivid::DrawText(40, "�߂ɂ݂��Ȃ���[", vivid::Vector2(0.0f, 150.0f), 0xff00ffff);
	if (skill_cool_flag)
		vivid::DrawText(40, "�X�L���N�[������[", vivid::Vector2(0.0f, 200.0f), 0xff00ffff);
	vivid::DrawText(40,"�L�������x�F" +  std::to_string(m_Velocity.x), vivid::Vector2(0.0f, 250.0f), 0xff00ffff);
	vivid::DrawText(40, "�L�����̐F�F" + std::to_string(color), vivid::Vector2(0.0f, 300.0f), 0xff00ffff);
	if (found_flag == true)
		vivid::DrawText(40, "���o���肠���[", vivid::Vector2(0.0f, 350.0f), 0xff00ffff);
	if (found_flag == false)
		vivid::DrawText(40, "���o����Ȃ���[", vivid::Vector2(0.0f, 350.0f), 0xff00ffff);
#endif
}

//���
void Character::Finalize(void)
{
}

//�X�e�[�W�̓����蔻��
void Character::StageHit()
{
	//��
	if (cPos.x < Stage::GetInstance().GetLWall(cPos, ch_width, ch_height))
	{
		cPos.x = Stage::GetInstance().GetLWall(cPos, ch_width, ch_height);
	}
	//�E
	if (cPos.x + ch_width > Stage::GetInstance().GetRWall(cPos, ch_width, ch_height))
	{
		cPos.x = Stage::GetInstance().GetRWall(cPos, ch_width, ch_height) - ch_width;
	}
	//�V��
	if (cPos.y < Stage::GetInstance().GetCeiling(cPos, ch_width, ch_height))
	{	
		cPos.y = Stage::GetInstance().GetCeiling(cPos, ch_width, ch_height);
	}
	//�n��
	RoundHit(Stage::GetInstance().GetRoundHeight(cPos, ch_width, ch_height));
}
void Character::HStageHit()
{
	//��
	if (cPos.x < Stage::GetInstance().GetLWall(cPos, ch_width, ch_height))
	{
		cPos.x = Stage::GetInstance().GetLWall(cPos, ch_width, ch_height);
	}
	//�E
	if (cPos.x + ch_width > Stage::GetInstance().GetRWall(cPos, ch_width, ch_height))
	{
		cPos.x = Stage::GetInstance().GetRWall(cPos, ch_width, ch_height) - ch_width;
	}
}

//�V��ƒn�ʂ̔���
void Character::VStageHit()
{
	//�n��
	RoundHit(Stage::GetInstance().GetRoundHeight(cPos, ch_width, ch_height));
	//�V��
	if (cPos.y < Stage::GetInstance().GetCeiling(cPos, ch_width, ch_height))
	{
		cPos.y = Stage::GetInstance().GetCeiling(cPos, ch_width, ch_height);
		m_Velocity.y = 0;
	}
}

//��ʒ[�̓����蔻��
void Character::CheckWindow(void)
{
	//��ʂ̍��[
	if (cPos.x < 0.0f + Scroll.x)
	{
		cPos.x = 0.0f + Scroll.x;
	}
	//��ʂ̉E�[
	if (cPos.x + ch_width > vivid::WINDOW_WIDTH + Scroll.x)
	{
		cPos.x = vivid::WINDOW_WIDTH - ch_width + Scroll.x;
	}
	//��ʂ̓V��
	if (cPos.y < 0.0f + Scroll.y)
	{
		cPos.y = 0.0f + Scroll.y;
	}
	//��ʂ̒��
	if (cPos.y + ch_height > vivid::WINDOW_HEIGHT + Scroll.y)
	{
		cPos.y = vivid::WINDOW_HEIGHT - ch_height + Scroll.y;
	}
}

//���@�̑���
void Character::KeyboardControl(void)
{
	namespace keyboard = vivid::keyboard;

	accelerator = vivid::Vector2::ZERO;

	//�f�t�H���g��walk_speed�ɂ���
	ch_speed = walk_speed;

	//���l�𒴂����瑬�x��0�ɂ��Ċ����̈ړ����~�߂�
	if (abs(m_Velocity.x) < cut_speed)
	{
		m_Velocity.x = 0.0f;
		if (m_LandingFlag)
		{
			chara_state = CHARA_STATE::WAIT;
		}
	}
	//�f�t�H���g�͑ҋ@��Ԃɂ���
	if (m_LandingFlag)
		chara_state = CHARA_STATE::WAIT;

	//��SHIFT�������Ă���Ԃ�dash_speed�ɂȂ�
	if (keyboard::Button(keyboard::KEY_ID::LSHIFT))
	{
		ch_speed = dash_speed;
		if (m_LandingFlag)
			chara_state = CHARA_STATE::WAIT;
	}

	//��CTRL�������Ă���Ԃ�sneak_speed�ɂȂ�
	if (keyboard::Button(keyboard::KEY_ID::LCONTROL))
	{
		ch_speed = sneak_speed;
		if (m_LandingFlag)
			chara_state = CHARA_STATE::SNEAKWAIT;
	}

	//�X�^�~�i��0�ł͂Ȃ������Ă��Ȃ����̓X�^�~�i���񕜂���
	if (!(chara_state == CHARA_STATE::RUN) && c_stamina_dash)
	{
		RecoveryStamina();
	}

	//�X�^�~�i�Q�[�W��0�̎���fatigue_speed�ɂȂ�
	if (!c_stamina_dash)
	{
		LimitStamina();
	}

	//E�L�[�������ƃX�L�����؂�ւ��
	if (keyboard::Trigger(keyboard::KEY_ID::E))
	{
		ChangeSkill();
	}

	//A�������Ă���Ԃ͍��ړ�
	if (keyboard::Button(keyboard::KEY_ID::A))
	{
		accelerator.x = -ch_speed;
		c_scale.x = -1.0f;
		//�_�b�V�����̃X�^�~�i����
		if (ch_speed == dash_speed && c_stamina_dash)
		{
			DashStamina();
		}

		CheckMoveState();
	}

	//D�������Ă���Ԃ͉E�ړ�
	if (keyboard::Button(keyboard::KEY_ID::D))
	{
		accelerator.x = ch_speed;
		c_scale.x = 1.0f;
		//�_�b�V�����̃X�^�~�i����
		if (ch_speed == dash_speed && c_stamina_dash)
		{
			DashStamina();
		}

		CheckMoveState();
	}

	//�W�����v�̏���
	//SPACE�������ƃW�����v����ɂȂ�
	if (keyboard::Trigger(keyboard::KEY_ID::SPACE) && m_LandingFlag)
	{
		accelerator.y += jump_speed;
		chara_state = CHARA_STATE::JUMP;
	}

	//Q�L�[�������ƃX�L������������
	if (keyboard::Trigger(keyboard::KEY_ID::Q))
	{
		//�d�����Ȃ��悤�ɂ��邽�߂Ƀt���O��ʂ�
		if (skill_active_flag == false && skill_cool_flag == false)
		{
			skill_active_flag = true;
		}
	}

	//�X�L���̓��쏈��
	SkillMove();

	//��������
	if (m_LandingFlag == false||1)
	{
		accelerator.y += fall_speed;
	}

	//�u�����������W��������
	m_Velocity += accelerator;
	cPos.x += m_Velocity.x;
	//�X�e�[�W�Ƃ̓����蔻��̊m�F
	HStageHit();

	cPos.y += m_Velocity.y;

	VStageHit();

	//��ʒ[�̔���
	CheckWindow();

	//�ړ��Ɋ���������
	m_Velocity.x *= m_friction;
}

void Character::ControllerControl(void)
{
	namespace controller = vivid::controller;

	accelerator = vivid::Vector2::ZERO;

	//�f�t�H���g��walk_speed�ɂ���
	ch_speed = walk_speed;

	//���l�𒴂����瑬�x��0�ɂ��Ċ����̈ړ����~�߂�
	if (abs(m_Velocity.x) < cut_speed)
	{
		m_Velocity.x = 0.0f;
		if (m_LandingFlag)
		{
			chara_state = CHARA_STATE::WAIT;
		}
	}
	//�f�t�H���g�͑ҋ@��Ԃɂ���
	if (m_LandingFlag)
		chara_state = CHARA_STATE::WAIT;

	//A�{�^���𒷉����Ń_�b�V������
	if (controller::Button(controller::DEVICE_ID::PLAYER1, controller::BUTTON_ID::A))
	{
		ch_speed = dash_speed;
		if (m_LandingFlag)
			chara_state = CHARA_STATE::WAIT;
	}

	//���{�^���𒷉����ł��Ⴊ�݂ɂȂ�
	if (controller::Button(controller::DEVICE_ID::PLAYER1, controller::BUTTON_ID::DOWN))
	{
		ch_speed = sneak_speed;
		if (m_LandingFlag)
			chara_state = CHARA_STATE::SNEAKWAIT;
	}
	
	//�X�^�~�i��0�ł͂Ȃ������Ă��Ȃ����̓X�^�~�i���񕜂���
	if (!(chara_state == CHARA_STATE::RUN) && c_stamina_dash)
	{
		RecoveryStamina();
	}

	//�X�^�~�i�Q�[�W��0�̎���fatigue_speed�ɂȂ�
	if (!c_stamina_dash)
	{
		LimitStamina();
	}
	//Y�{�^������������X�L�����؂�ւ��
	if (controller::Trigger(controller::DEVICE_ID::PLAYER1, controller::BUTTON_ID::Y))
	{
		ChangeSkill();
	}
	//�\�����������ō��ړ�
	if (controller::Button(controller::DEVICE_ID::PLAYER1, controller::BUTTON_ID::LEFT))
	{
		accelerator.x = -ch_speed;
		c_scale.x = -1.0f;
		//�_�b�V�����̃X�^�~�i����
		if (ch_speed == dash_speed && c_stamina_dash)
		{
			DashStamina();
		}

		CheckMoveState();
	}
	//�\���E�������ŉE�ړ�
	if (controller::Button(controller::DEVICE_ID::PLAYER1, controller::BUTTON_ID::RIGHT))
	{
		accelerator.x = ch_speed;
		c_scale.x = 1.0f;
		//�_�b�V�����̃X�^�~�i����
		if (ch_speed == dash_speed && c_stamina_dash)
		{
			DashStamina();
		}

		CheckMoveState();
	}

	//B�{�^���������ƃW�����v������
	if ((controller::Trigger(controller::DEVICE_ID::PLAYER1, controller::BUTTON_ID::B)) && m_LandingFlag)
	{
		accelerator.y += jump_speed;
		chara_state = CHARA_STATE::JUMP;
	}
	//X�{�^���������ƃX�L������������
	if (controller::Trigger(controller::DEVICE_ID::PLAYER1, controller::BUTTON_ID::X))
	{
		//�d�����Ȃ��悤�ɂ��邽�߂Ƀt���O��ʂ�
		if (skill_active_flag == false && skill_cool_flag == false)
		{
			skill_active_flag = true;
		}
	}
	
	//�X�L���̓��쏈��
	SkillMove();

	//��������
	if (m_LandingFlag == false || 1)
	{
		accelerator.y += fall_speed;
	}

	//�u�����������W��������
	m_Velocity += accelerator;
	cPos.x += m_Velocity.x;
	//�X�e�[�W�Ƃ̓����蔻��̊m�F
	HStageHit();

	cPos.y += m_Velocity.y;

	VStageHit();

	//��ʒ[�̔���
	CheckWindow();

	//�ړ��Ɋ���������
	m_Velocity.x *= m_friction;
}

//�n�ʂƂ̓����蔻��
void Character::RoundHit(float rHeight)
{
	if (cPos.y + ch_height < rHeight)
	{
		m_LandingFlag = false;
	}
		if (cPos.y + ch_height > rHeight && cPos.y < rHeight) {
			cPos.y = rHeight - ch_height;
			m_Velocity.y = 0.0f;
			//�n�ʂƓ���������ڒn�t���O��true�ɂ���
			m_LandingFlag = true;
		}
}

//�ǂ̗��Ɏ��@�����ׂĉB��Ă�����F��ς���
bool Character::CheckWallHit(vivid::Vector2 wPos, float wWidth, float wHeight)
{
	return Stage::GetInstance().CheckHitWallPlayer(cPos, ch_height, ch_width);
	if ((wPos.x <= cPos.x) && (wPos.x + wWidth >= cPos.x + ch_width) && (wPos.y <= cPos.y) && (wPos.y + wHeight >= cPos.y + ch_height))
	{
		return true;
	}
	else
	{
		return false;
	}
}

//�G�̎��E�ɓ�������true��Ԃ��A���E�̊O�̎���false��Ԃ�
bool Character::CheckEnemyHit(vivid::Vector2 ePos, float eRadius)
{
	//�_�Ƌ�`�̔��肻��1(����)
	bool result_h = ePos.x > cPos.x - eRadius
		&& ePos.x < cPos.x + ch_width + eRadius
		&& ePos.y > cPos.y
		&& ePos.y < cPos.y + ch_height;

	//�_�Ƌ�`�̔��肻��2(�c��)
	bool result_v = ePos.x > cPos.x
		&& ePos.x < cPos.x + ch_width
		&& ePos.y > cPos.y - eRadius
		&& ePos.y < cPos.y + ch_height + eRadius;

	//�_�Ɖ~�̔���	
	//���@�̍���(LeftUpper)
	vivid::Vector2 v = ePos - cPos;
	bool result_lu = v.Length() <= eRadius;		
	//���@�̉E��(RightUpper)
	v = ePos - vivid::Vector2(cPos.x + ch_width, cPos.y);
	bool result_ru = v.Length() <= eRadius;
	//���@�̍���(LeftDown)
	v = ePos - vivid::Vector2(cPos.x, cPos.y + ch_height);
	bool result_ld = v.Length() <= eRadius;
	//���@�̉E��(RightDown)
	v = ePos - vivid::Vector2(cPos.x + ch_width, cPos.y + ch_height);
	bool result_rd = v.Length() <= eRadius;
	//��L�̔��肩�瓖�����Ă��邩(���E�ɓ����Ă��邩)�𔻒f����
	if (result_h || result_v || result_lu || result_ru || result_ld || result_rd)
	{
		if (found_flag == false)
		{
			return false;
		}
		return true;
	}
	//�������Ă��Ȃ��ꍇ��false��Ԃ�
	else
	{
		return false;
	}
}

//�A�C�e���Ƃ̓����蔻��
bool Character::CheckObtainItem(vivid::Vector2 iPos, vivid::Vector2 iCenter, float iWidth, float iHeight)
{
	//�Ίp���ƃx�N�g���ŏ������s��(�P�u���b�N�Ɏg�p����)
	float a1 = -iHeight / iWidth;
	float a2 = iHeight / iWidth;
	float a3 = (cPos.y - iCenter.y) / (cPos.x - iPos.x);

	if (cPos.x < iPos.x + iWidth && cPos.x + ch_width > iPos.x
		&& cPos.y < iPos.y + iHeight && cPos.y + ch_height > iPos.y)
	{
		if (vivid::keyboard::Trigger(vivid::keyboard::KEY_ID::F))
		{
			cCatch = true;
			return true;
		}
	}
	return false;
}

//�����������ɂ��ꂼ��F��ς���
void Character::CheckHit(vivid::Vector2 wPos, float wWidth, float wHeight, vivid::Vector2 ePos, float eRadius)
{
	//�ǂɓ���������(��Q���ɉB�ꂽ�Ƃ�)
	if (CheckWallHit(wPos, wWidth, wHeight))
	{
#ifdef _DEGUB
		color = 0xff0000ff;
#endif // DEBUG
	}
	//��Q���̊O�œG�̎��E�ɓ�������
	else if (CheckEnemyHit(ePos, eRadius))
	{
#ifdef _DEBUG
		color = 0xffff0000;
#endif // DEBUG
	}
	//�f�t�H���g�̏��
	else
	{
#ifdef _DEBUG
		color = 0xffffffff;
#endif // DEBUG
	}
}

//�G���Q���Ƃ̓����蔻��
void Character::CheckHit(vivid::Vector2 wPos, float wWidth, float wHeight, bool EnemyHitFlg)
{	
	//�ǂɓ���������(��Q���ɉB�ꂽ�Ƃ�)
	if (CheckWallHit(wPos, wWidth, wHeight))
	{
#ifdef _DEBUG
		color = 0xff0000ff;
#endif // DEBUG
		cShielding = true;
	}
	//��Q���̊O�œG�̎��E�ɓ�������
	else if (EnemyHitFlg)
	{
#ifdef _DEBUG
		color = 0xffff0000;
#endif // DEBUG
		cShielding = false;
	}
	//�f�t�H���g�̏��
	else
	{
#ifdef _DEBUG
		color = 0xffffffff;
#endif // DEBUG
		cShielding = false;
	}
}

//��������������s��������Ԃ��t���O
bool Character::CheckThrow(void)
{
	if (cCatch)
	{
		if (vivid::keyboard::Trigger(vivid::keyboard::KEY_ID::C))
		{
			return true;
		}
		return false;
	}
}

//�A�C�e����u����������s��������Ԃ�
bool Character::checkPut(void)
{
	if (cCatch)
	{
		if (vivid::keyboard::Trigger(vivid::keyboard::KEY_ID::R))
		{
			return true;
		}
		return false;
	}
}

//�A�j���[�V�����̍X�V
void Character::UpdateAnimation(void)
{
	//��Ԃ��ƂɃA�j���[�V�����̍ő喇���̐ݒ�
	switch (chara_state)
	{
	case CHARA_STATE::WAIT:
		c_change_anime_frame = 12;
		break;
	case CHARA_STATE::WALK:
		c_change_anime_frame = 18;
		break;
	case CHARA_STATE::RUN:
		c_change_anime_frame = 9;
		break;
	case CHARA_STATE::SNEAKWAIT:
		c_change_anime_frame = 12;
		break;
	case CHARA_STATE::SNEAKWALK:
		c_change_anime_frame = 15;
		break;
	case CHARA_STATE::JUMP:
		c_change_anime_frame = 8;
		break;
	}

	//->�A�j���[�V�����̍X�V
	c_anime_timer++;

	if (c_anime_timer >= c_change_anime_timer)
	{
		c_anime_frame++;
		if (c_anime_frame == c_change_anime_frame)
		{
			c_anime_frame = 0;
		}
		c_anime_timer = 0;
	}
	//<-�A�j���[�V�����̍X�V
}

//���@���ڒn���Ă����Ԃ̕ύX����
void Character::CheckMoveState(void)
{
	if (m_LandingFlag)
	{
		chara_state = CHARA_STATE::WALK;
		if (ch_speed == dash_speed)
		{
			chara_state = CHARA_STATE::RUN;
		}
		if (ch_speed == sneak_speed)
		{
			chara_state = CHARA_STATE::SNEAKWALK;
		}
	}
}

//�X�^�~�i�̏����
void Character::DashStamina(void)
{
	//�X�^�~�i�Q�[�W�Ɏc�ʂ����鎞���̊m�F
	if (c_stamina_gauge > 0)
	{
	//�X�^�~�i����̃J�E���^��i�߂�
		c_stamina_count++;
	//�J�E���^����l�ɒB������X�^�~�i�Q�[�W���炷
		if (c_stamina_count >= 60)
		{
			c_stamina_gauge--;
			c_stamina_count = 0;
		}
	}
	//�X�^�~�i��0�ɂȂ�����̏���
	else
	{
		c_stamina_dash = false;
	}
	//�X�^�~�i�񕜊J�n�̃J�E���^�̃��Z�b�g
	c_stamina_recovery = 0;
}

//�X�^�~�i�̉񕜏���
void Character::RecoveryStamina(void)
{
	c_stamina_recovery++;
	if (c_stamina_gauge < c_max_stamina)
	{
		if (c_stamina_recovery >= 60)
		{
			c_stamina_gauge++;
			c_stamina_count = 0;
			c_stamina_recovery = 0;
		}
	}
}

//�X�^�~�i��0�ɂȂ�����̉񕜏���
void Character::LimitStamina(void)
{
	ch_speed = fatigue_speed;
	c_limit_recovery++;
	if (c_limit_recovery >= 90)
	{
		if (c_stamina_gauge < c_max_stamina)
		{
			c_stamina_gauge++;
			c_limit_recovery = 0;
		}
		if (c_stamina_gauge == c_max_stamina)
		{
			c_stamina_dash = true;
		}
	}
}

//�X�L��������̏���
void Character::SkillMove(void)
{
	//�X�L���̃A�N�e�B�u�t���O��true�̎��ɏ������s��
	if (skill_active_flag)
	{
		active_count++;
		if (active_count < activation_time)
		{
			switch ((skill_memory))
			{
			case (int)CHARA_SKILL::ANIMALLEG:
				accelerator *= 1.6f;
				chara_skill = CHARA_SKILL::ANIMALLEG;
				break;
			case (int)CHARA_SKILL::INVISIBLE:
				chara_skill = CHARA_SKILL::INVISIBLE;
				color = 0x44ffffff;
				found_flag = false;
				break;
			}
		}
		//�^�C�}�[���K��l�𒴂�����e���l�����Z�b�g����
		if (active_count >= activation_time)
		{
			switch (skill_memory)
			{
			case (int)CHARA_SKILL::ANIMALLEG:
				accelerator *= 0.625f;
				break;
			case (int)CHARA_SKILL::INVISIBLE:
				color = 0xffffffff;
				found_flag = true;
				break;
			default:
				break;
			}
			chara_skill = CHARA_SKILL::NORMAL;
			active_count = 0;
			skill_active_flag = false;
			skill_cool_flag = true;
		}
	}
}

//�X�L���̐؂�ւ�����
void Character::ChangeSkill(void)
{
	if (skill_active_flag == false)
	{
		switch (skill_memory)
		{
		case (int)CHARA_SKILL::INVISIBLE:
			skill_memory = (int)CHARA_SKILL::ANIMALLEG;
			break;

		case (int)CHARA_SKILL::ANIMALLEG:
			skill_memory = (int)CHARA_SKILL::INVISIBLE;
			break;
		}
	}
}

//�X�L���̃N�[���^�C������
void Character::CoolTime(void)
{
	if (skill_cool_flag)
	{
		cool_time_count++;
		if (cool_time_count >= skill_cool_time)
		{
			cool_time_count = 0;
			skill_cool_flag = false;
		}
	}
}

//�X�^�~�i�̕`���؂�ւ��鏈��
void Character::StaminaDraw(void)
{
	namespace keyboard = vivid::keyboard;
	namespace controller = vivid::controller;

	//�_�b�V���{�^���������Ă���Ԃ͕`��t���O��true�ɂ��ĕ`��J�E���^�����Z�b�g����
	if ((keyboard::Button(keyboard::KEY_ID::LSHIFT)) || (controller::Button(controller::DEVICE_ID::PLAYER1, controller::BUTTON_ID::A)))
	{
		c_stamina_draw = true;
		c_stamina_draw_count = 0;
	}
	//�����Ă��Ȃ����ɃX�^�~�i���ő�l��������J�E���^��i�߁A�K��l�ɒB������`��t���O��false�ɂ��ăJ�E���^�����Z�b�g����
	else
	{
		if (c_stamina_gauge == c_max_stamina)
		{
			c_stamina_draw_count++;
			if (c_stamina_draw_count >= c_draw_stamina)
			{
				c_stamina_draw = false;
				c_stamina_draw_count = 0;
			}
		}
	}
}

//�X�N���[���̍X�V
void Character::Scroll_Update()
{
	if (cPos.x > Scroll.x + vivid::WINDOW_WIDTH - scroll_width_space)
		Scroll.x = cPos.x - vivid::WINDOW_WIDTH + scroll_width_space;
	if (Scroll.x > Stage::GetInstance().GetStageWidthSize() - vivid::WINDOW_WIDTH)
		Scroll.x = Stage::GetInstance().GetStageWidthSize() - vivid::WINDOW_WIDTH;
	if (cPos.x < Scroll.x + scroll_width_space)
		Scroll.x = cPos.x - scroll_width_space;
	if (Scroll.x < 0)
		Scroll.x = 0;

	if (cPos.y > Scroll.y + vivid::WINDOW_HEIGHT - scroll_height_space)
		Scroll.y = cPos.y - vivid::WINDOW_HEIGHT + scroll_height_space;
	if (Scroll.y > Stage::GetInstance().GetStageHeightSize() - vivid::WINDOW_HEIGHT)
		Scroll.y = Stage::GetInstance().GetStageHeightSize() - vivid::WINDOW_HEIGHT;
	if (cPos.y < Scroll.y + scroll_height_space)
		Scroll.y = cPos.y - scroll_height_space;
	if (Scroll.y < 0)
		Scroll.y = 0;
}