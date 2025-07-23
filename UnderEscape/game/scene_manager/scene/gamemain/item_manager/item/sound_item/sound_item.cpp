#include "sound_item.h"

const float SoundItem::item_height = 32.0f;
const float SoundItem::item_width = 32.0f;
const float SoundItem::item_radius = 16.0f;



SoundItem::SoundItem()
	: Item(ItemID::SOUND_ITEM, ITEM_STATE::PLACE,item_width,item_height,item_radius)
	, Xspeed(100.0f) //�򋗗��̃}�C�i�X�{��(X��)�l������������Ɣ򋗗����L�т�
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
	vivid::DrawTexture("data\\ball.png", iPos, iColor);
}



void SoundItem::GetMove(vivid::Vector2 cPos, float cWidth, float cHeight)
{
	if (catchFlg == true && vivid::keyboard::Trigger(vivid::keyboard::KEY_ID::C))
	{
		m_ItemState = ITEM_STATE::USE;
		catchFlg = false;
		Mouse.x = (vivid::mouse::GetCursorPos().x) - cPos.x; 
		Mouse.y = cPos.y - vivid::mouse::GetCursorPos().y;
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

		if (iPos.y + item_height < rHeight)
		{
			iPos.x += Mouse.x / Xspeed;
			iPos.y += V + (item_fall * Ga);
			iColor = 0xff00ffff;
		}

		if (iPos.y + item_height >= rHeight)
		{
			iPos.y = rHeight - item_height;
			m_ItemState = ITEM_STATE::PLACE;
			iColor = 0xffffffff;
		}
		Ga += 0.981;
}


