#include "sound_item.h"

const float SoundItem::item_height = 32.0f;
const float SoundItem::item_width = 32.0f;
const float SoundItem::item_radius = 16.0f;



SoundItem::SoundItem()
	: Item(ItemID::SOUND_ITEM, ITEM_STATE::PLACE,item_width,item_height,item_radius)
	, Xspeed(50.0f) //�򋗗��̃}�C�i�X�{��(X��)�l������������Ɣ򋗗����L�т�
	, Yspeed(20.0f) //�򋗗��̃}�C�i�X�{��(Y��)�l������������Ɣ򋗗����L�т�
	, Mouse(0.0f, 0.0f)
	
	
{
}

SoundItem::~SoundItem()
{
}

void SoundItem::Initialize(vivid::Vector2 position)
{
	iPos.x = position.x-item_width;
	iPos.y = position.y - item_height;
	iColor = 0xffffffff;
	iCenter.x = (iPos.x + item_width) / 2;
	iCenter.y = (iPos.y + item_height) / 2;
}


void SoundItem::Draw(void)
{
	vivid::DrawTexture("data\\ball.png", iPos - Character::GetInstance().GetScroll(), iColor);
}



void SoundItem::GetMove(vivid::Vector2 cPos, float cWidth, float cHeight)
{
	if (catchFlg == true && vivid::keyboard::Trigger(vivid::keyboard::KEY_ID::C))
	{
		m_ItemState = ITEM_STATE::USE;
		catchFlg = false;
		Mouse.x = (vivid::mouse::GetCursorPos().x)+ Character::GetInstance().GetScroll().x - cPos.x;
		Mouse.y = cPos.y - vivid::mouse::GetCursorPos().y + Character::GetInstance().GetScroll().y;
		
	}

	if (catchFlg)
	{
		iPos.x = cPos.x + cWidth;
		iPos.y = cPos.y + (cHeight / 2);
		iCenter.x = (iPos.x + item_width) / 2;
		iCenter.y = (iPos.y + item_height) / 2;
		iColor = 0xffff00ff;
	}
	Ga = 1.0;
	V = 0.0;
}

void SoundItem::UseMove(float rHeight, vivid::Vector2 c_pos)
{
	
		catchFlg = false;

		V = -(Mouse.y / Yspeed);
		//�A�C�e���I�u�W�F�N�g�̍��W�X�V
		if (iPos.y  <= Stage::GetInstance().GetRoundHeight(iPos,m_Width,m_Height) - m_Height)
		{
			iPos.x += Mouse.x / Xspeed;
			iPos.y += V + (item_fall * Ga);
			iColor = 0xff00ffff;
		}

		//�n�ʔ���
		if (iPos.y  >= Stage::GetInstance().GetRoundHeight(iPos, m_Width, m_Height) - m_Height)
		{
			iPos.y =Stage::GetInstance().GetRoundHeight(iPos, m_Width, m_Height) - m_Height;
			m_ItemState = ITEM_STATE::PLACE;
			iColor = 0xffffffff;
		}
		//���ǔ���
		if (iPos.x < Stage::GetInstance().GetLWall(iPos, m_Width, m_Height))
		{
		}
		//�E�ǔ���
		
		//�V�䔻��

		//�d�͉����x�̍X�V
		Ga += 0.981;
}


