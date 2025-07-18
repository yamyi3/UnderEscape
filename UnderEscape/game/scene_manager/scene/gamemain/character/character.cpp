#include "character.h"
#include "../stage/stage.h"

float	Character::ch_speed = sneak_speed;
unsigned Character::color = 0xffffffff;
bool	Character::m_LandingFlag = false;
bool	Character::cCatch = false;
bool	Character::cAlive = true;
int		Character::gauge = 0;
int		Character::gauge_count_frame = 0;
int		Character::down_gauge_count = 0;
CHARA_SKILL chara_skill = CHARA_SKILL::ANIMALLEG;

const float Character::ch_width		 = 72.0f;	//���@�̕�
const float Character::ch_height	 = 180.0f;	//���@�̍���
const float Character::walk_speed	 = 1.2f;	//���@�̒ʏ�ړ����x
const float Character::dash_speed	 = 2.4f;	//���@�̃_�b�V�����̈ړ����x
const float Character::sneak_speed	 = 0.6f;	//���@�̕��s���̈ړ����x
const float Character::fatigue_speed = 0.3f;	//���@�̔�J���̈ړ����x

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
	cPos = {100.0f, rPos.y - ch_height};
	gPos = { 0.0f, 0.0f };
	gauge_rect.top = 0;
	gauge_rect.bottom = 30;
	gauge_rect.left = 0;
	gauge_rect.right = 20 * gauge;
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
	active_count = 0;
}

void Character::Update(void)
{
	//���@�̑���
	Control();
	//��ʒ[�̔���
	CheckWindow();
	//�X�e�[�W�Ƃ̓����蔻��
	StageHit();
	//�A�j���[�V�����̍X�V
	UpdateAnimation();
	//�X�L��������̏���
	SkillMove();
	//�X�N���[���̍X�V
	Scroll_Update();
}

void Character::Draw(void)
{
	stamina_pos.x = (float)(((cPos.x + (ch_width / 2.0f))- (stamina_width / 2.0f)));
	stamina_pos.y = (float)(cPos.y - 20);

	vivid::Rect g_rect;
	g_rect.top = 0;
	g_rect.bottom = 30;
	g_rect.left = 0;
	g_rect.right = 200;

	gauge_rect.top = 0;
	gauge_rect.bottom = 30;
	gauge_rect.left = 0;
	gauge_rect.right = 20 * gauge;

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

	vivid::DrawTexture(c_image[(int)chara_state], cPos - Scroll, color, c_rect, c_anchor, c_scale);
	vivid::DrawTexture("data\\gauge.png", gPos - Scroll, 0xffffffff, g_rect);
	vivid::DrawTexture("data\\gauge.png", gPos - Scroll, 0xff00ffff, gauge_rect);
	vivid::DrawTexture(c_dash_image[c_stamina_dash], stamina_pos - Scroll, 0xffffffff, stamina_rect, stamina_anchor, stamina_scale);

#ifdef _DEBUG

	if (skill_active_flag == false)
		vivid::DrawText(40, "����������ĂȂ���[", vivid::Vector2(0.0f, 50.0f), 0xff00ffff);
	if (skill_active_flag)
		vivid::DrawText(40, "�����������[", vivid::Vector2(0.0f, 50.0f), 0xff00ffff);
	if (chara_skill == CHARA_SKILL::ANIMALLEG)
		vivid::DrawText(40, "�����悢��[", vivid::Vector2(0.0f, 100.0f), 0xff00ffff);
	if (chara_skill == CHARA_SKILL::INVISIBLE)
		vivid::DrawText(40, "�߂ɂ݂��Ȃ���[", vivid::Vector2(0.0f, 150.0f), 0xff00ffff);
#endif
}

void Character::Finalize(void)
{
}

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
void Character::Control(void)
{
	namespace keyboard = vivid::keyboard;

	vivid::Vector2 accelerator = {};

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

	//A�������Ă���Ԃ͍��ړ�
	if (keyboard::Button(keyboard::KEY_ID::A))
	{
		accelerator.x = -ch_speed;
		c_scale.x = -1.0f;
		CheckMoveState();
	}

	//D�������Ă���Ԃ͉E�ړ�
	if (keyboard::Button(keyboard::KEY_ID::D))
	{
		accelerator.x = ch_speed;
		c_scale.x = 1.0f;
		CheckMoveState();
	}

	//Q�L�[�������ƃX�L������������
	if (keyboard::Trigger(keyboard::KEY_ID::Q))
	{
		//�d�����Ȃ��悤�ɂ��邽�߂Ƀt���O��ʂ�
		if (skill_active_flag == false)
		{
			skill_active_flag = true;
		}
	}

	//E�L�[�������ƃX�L�����؂�ւ��
	if (keyboard::Trigger(keyboard::KEY_ID::E))
	{
			ChangeSkill();
	}

	//�W�����v�̏���
	//SPACE�������ƃW�����v����ɂȂ�
	if (keyboard::Trigger(keyboard::KEY_ID::SPACE) && m_LandingFlag)
	{
		accelerator.y += jump_speed;
		chara_state = CHARA_STATE::JUMP;
	}

	//��������
	if (m_LandingFlag == false||1)
	{
		accelerator.y += fall_speed;
	}

	m_Velocity += accelerator;
	cPos += m_Velocity;

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
		return true;
	}
	//�������Ă��Ȃ��ꍇ��false��Ԃ�
	else
	{
		return false;
	}
}

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
		DownerGauge();
#ifdef _DEGUB
		color = 0xff0000ff;
#endif // DEBUG
	}
	//��Q���̊O�œG�̎��E�ɓ�������
	else if (CheckEnemyHit(ePos, eRadius))
	{
		UpperGauge();
#ifdef _DEBUG
		color = 0xffff0000;
#endif // DEBUG
	}
	//�f�t�H���g�̏��
	else
	{
		DownerGauge();
#ifdef _DEBUG
		color = 0xffffffff;
#endif // DEBUG
	}
}

void Character::CheckHit(vivid::Vector2 wPos, float wWidth, float wHeight, bool EnemyHitFlg)
{	
	//�ǂɓ���������(��Q���ɉB�ꂽ�Ƃ�)
	if (CheckWallHit(wPos, wWidth, wHeight))
	{
		DownerGauge();

#ifdef _DEBUG
		color = 0xff0000ff;
#endif // DEBUG
		cShielding = true;
	}
	//��Q���̊O�œG�̎��E�ɓ�������
	else if (EnemyHitFlg)
	{
		UpperGauge();
#ifdef _DEBUG
		color = 0xffff0000;
#endif // DEBUG
		cShielding = false;
	}
	//�f�t�H���g�̏��
	else
	{
		DownerGauge();
#ifdef _DEBUG
		color = 0xffffffff;
#endif // DEBUG
		cShielding = false;
	}
}

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

void Character::UpperGauge(void)
{
	down_gauge_count = 0;
	gauge_count_frame++;
	if (gauge_count_frame == one_gauge_frame)
	{
		if (gauge < max_gauge)
		{
			gauge++;
			gauge_count_frame = 0;
		}
		if (gauge >= max_gauge)
		{
			//�I���
			vivid::DrawText(40, "����肾��[", vivid::Vector2(800.0f, 500.0f));
		}
	}
}

void Character::DownerGauge(void)
{
	down_gauge_count++;
	if (down_gauge_count >= downer_frame)
	{
		if (gauge > 0)
		{
			gauge--;
		}
		down_gauge_count = 0;
	}
}

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

void Character::CheckMoveState(void)
{
	if (m_LandingFlag)
	{
		chara_state = CHARA_STATE::WALK;
		if (ch_speed == dash_speed)
		{
			chara_state = CHARA_STATE::RUN;
			if (c_stamina_dash)
			{
				DashStamina();
			}
		}
		if (ch_speed == sneak_speed)
		{
			chara_state = CHARA_STATE::SNEAKWALK;
		}
	}
}

void Character::DashStamina(void)
{
	//�X�^�~�i�Q�[�W�Ɏc�ʂ����鎞�̏���
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
			switch (chara_skill)
			{
			case CHARA_SKILL::ANIMALLEG:
				ch_speed *= 2.0f;
				break;
			case CHARA_SKILL::INVISIBLE:
				color = 0x00000000;
				break;
			}
		}
		//�^�C�}�[���K��l�𒴂�����e���l�����Z�b�g����
		if (active_count >= activation_time)
		{
			switch (chara_skill)
			{
			case CHARA_SKILL::ANIMALLEG:
				ch_speed /= 2.0f;
				break;
			case CHARA_SKILL::INVISIBLE:
				color = 0xffffffff;
				break;
			default:
				break;
			}
			active_count = 0;
			skill_active_flag = false;
		}
	}
}

//�X�L���̐؂�ւ�����
void Character::ChangeSkill(void)
{
	switch (chara_skill)
	{
	case CHARA_SKILL::INVISIBLE:
		chara_skill = CHARA_SKILL::ANIMALLEG;
		break;

	case CHARA_SKILL::ANIMALLEG:
		chara_skill = CHARA_SKILL::INVISIBLE;
		break;
	}
}

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