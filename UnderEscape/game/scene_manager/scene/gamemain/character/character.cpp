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

const float Character::ch_width		= 72.0f;	//���@�̕�
const float Character::ch_height	= 180.0f;	//���@�̍���
const float Character::walk_speed	= 0.6f;		//���@�̒ʏ�ړ����x
const float Character::dash_speed	= 1.2f;		//���@�̃_�b�V�����̈ړ����x
const float Character::sneak_speed	= 0.3f;		//���@�̕��s���̈ړ����x


const int Character::tentacle_CT = 300;
const int Character::tentacle_move_time = 20;

Character::Character()
	:TentacleCTTimer(0)
{}

Character& Character::GetInstance(void)
{
	static Character	instance;
	return instance;
}

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
	c_anime_frame = 0;			//�e���[�V�����摜�؂�ւ�����
	c_anime_timer = 0;
	c_change_anime_timer = 15;
	c_change_anime_frame = 0;
}

void Character::Update(void)
{
	if(TentacleCTTimer>0)
	TentacleCTTimer--;
	if (chara_skill_state==SKILL_STATE::TENTACLE)
	{
		TentacleUpdate();
	}
	else
	Control();
	CheckWindow();
	UpdateAnimation();
}

void Character::Draw(void)
{
	vivid::Rect g_rect;
	g_rect.top = 0;
	g_rect.bottom = 30;
	g_rect.left = 0;
	g_rect.right = 200;

	gauge_rect.top = 0;
	gauge_rect.bottom = 30;
	gauge_rect.left = 0;
	gauge_rect.right = 20 * gauge;

	c_rect.top = 0;
	c_rect.bottom = ch_height;
	c_rect.left = ch_width * (c_anime_frame % c_change_anime_frame);
	c_rect.right = c_rect.left + ch_width;

	//vivid::DrawTexture("data\\���u���l��\\minihuman����1.png", cPos, color, c_rect);
	vivid::DrawTexture(c_image[(int)chara_state], cPos, color, c_rect, c_anchor, c_scale);
	vivid::DrawTexture("data\\gauge.png", gPos, 0xffffffff, g_rect);
	vivid::DrawTexture("data\\gauge.png", gPos, 0xff00ffff, gauge_rect);
}

void Character::Finalize(void)
{
}

//��ʒ[�̓����蔻��
void Character::CheckWindow(void)
{
	//��ʂ̍��[
	if (cPos.x < 0.0f)
	{
		cPos.x = 0.0f;
	}
	//��ʂ̉E�[
	if (cPos.x + ch_width > vivid::WINDOW_WIDTH)
	{
		cPos.x = vivid::WINDOW_WIDTH - ch_width;
	}
	//��ʂ̓V��
	if (cPos.y < 0.0f)
	{
		cPos.y = 0.0f;
	}
	//��ʂ̒��
	if (cPos.y + ch_height > vivid::WINDOW_HEIGHT)
	{
		cPos.y = vivid::WINDOW_HEIGHT - ch_height;
	}
}

//���@�̑���
void Character::Control(void)
{
	namespace keyboard = vivid::keyboard;

	vivid::Vector2 accelerator = {};

	//�f�t�H���g��walk_speed�ɂ���
	ch_speed = walk_speed;
	if (m_LandingFlag)
		chara_state = CHARA_STATE::WAIT;

	//���l�𒴂����瑬�x��0�ɂ��Ċ����̈ړ����~�߂�
	if (abs(m_Velocity.x) < cut_speed && m_LandingFlag)
	{
		m_Velocity.x = 0.0f;
		chara_state = CHARA_STATE::WAIT;
	}

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
	//A�������Ă���Ԃ͍��ړ�
	if (keyboard::Button(keyboard::KEY_ID::A))
	{
		accelerator.x = -ch_speed;
		c_scale.x = -1.0f;
		if (m_LandingFlag)
			chara_state = CHARA_STATE::WALK;
		//������͂����Ă����Ԃ������瑖�胂�[�V�����ɂȂ�
		if (ch_speed == dash_speed && m_LandingFlag)
		{
			chara_state = CHARA_STATE::RUN;
		}
		//���Ⴊ�ݓ��͂����Ă����Ԃ������炵�Ⴊ�ݕ������[�V�����ɂȂ�
		if (ch_speed == sneak_speed && m_LandingFlag)
		{
			chara_state = CHARA_STATE::SNEAKWALK;
		}
	}

	//D�������Ă���Ԃ͉E�ړ�
	if (keyboard::Button(keyboard::KEY_ID::D))
	{
		accelerator.x = ch_speed;
		c_scale.x = 1.0f;
		if (m_LandingFlag)
			chara_state = CHARA_STATE::WALK;
		//������͂����Ă����Ԃ������瑖�胂�[�V�����ɂȂ�
		if (ch_speed == dash_speed && m_LandingFlag)
		{
			chara_state = CHARA_STATE::RUN;
		}
		//���Ⴊ�ݓ��͂����Ă����Ԃ������炵�Ⴊ�ݕ������[�V�����ɂȂ�
		if (ch_speed == sneak_speed && m_LandingFlag)
		{
			chara_state = CHARA_STATE::SNEAKWALK;
		}
	}

	
	//�W�����v�̏���
	//SPACE�������ƃW�����v����ɂȂ�
	if (keyboard::Trigger(keyboard::KEY_ID::SPACE) && m_LandingFlag)
	{
		accelerator.y += jump_speed;
		//�ڒn�t���O��false�ɂ��ċ󒆃W�����v���o���Ȃ��悤�ɂ���
		m_LandingFlag = false;
		chara_state = CHARA_STATE::JUMP;
	}

	//��������
	if (m_LandingFlag == false)	
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
		color = 0xff0000ff;
	}
	//��Q���̊O�œG�̎��E�ɓ�������
	else if (CheckEnemyHit(ePos, eRadius))
	{
		UpperGauge();
		color = 0xffff0000;
	}
	//�f�t�H���g�̏��
	else
	{
		DownerGauge();
		color = 0xffffffff;
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
	}
	//��Q���̊O�œG�̎��E�ɓ�������
	else if (EnemyHitFlg)
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
			cAlive = false;
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
}

void Character::ChangeTentacle()
{
	if (chara_skill_state != SKILL_STATE::TENTACLE&& TentacleCTTimer<=0)
	{
		TentacleCTTimer = tentacle_CT;
		chara_skill_state = SKILL_STATE::TENTACLE;
		vivid::Point mpos = vivid::mouse::GetCursorPos();
		vivid::Vector2 mopos;
		c_TentaclePos.x = mpos.x;
		c_TentaclePos.y = mpos.y;
		TentacleCount = 0;
		cPosLog = cPos;
		m_LandingFlag = false;
		chara_state = CHARA_STATE::JUMP;
		if (cPos.x < c_TentaclePos.x)
		{
			c_scale.x = 1.0f;
		}
		if (cPos.x > c_TentaclePos.x)
		{
			c_scale.x = -1.0f;
		}
	}
}

void Character::TentacleUpdate()
{
	TentacleCount++;
	cPos.x -= (cPosLog.x - c_TentaclePos.x) / tentacle_move_time;
	cPos.y -= (cPosLog.y - c_TentaclePos.y) / tentacle_move_time;
	if (TentacleCount >= tentacle_move_time ||chara_state!=CHARA_STATE::JUMP|| m_LandingFlag)
	{
		chara_skill_state = SKILL_STATE::DEFAULT;
	}
}
