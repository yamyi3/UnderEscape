#include "sound_item.h"

const float SoundItem::item_height = 32.0f;
const float SoundItem::item_width = 32.0f;
const float SoundItem::item_radius = 16.0f;



SoundItem::SoundItem()
	: Item(ITEM_ID::SOUND_ITEM, ITEM_STATE::PLACE,item_width,item_height,item_radius)

	, Xspeed(50.0f) //飛距離のマイナス倍率(X軸)値を小さくすると飛距離が伸びる
	, Yspeed(50.0f) //飛距離のマイナス倍率(Y軸)値を小さくすると飛距離が伸びる
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
		Mouse.y = cPos.y - (vivid::mouse::GetCursorPos().y + Character::GetInstance().GetScroll().y);
		
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
	m_Velocity = vivid::Vector2(0.0f, 0.0f); // 重力加速度をリセット
}

void SoundItem::UseMove(vivid::Vector2 c_pos)
{
	//アイテムオブジェクトの座標更新

		catchFlg = false;


		m_Velocity.y = -(Mouse.y / Yspeed);
		m_Velocity.x = (Mouse.x / Xspeed);
		//壁に触れたらその場で自由落下
		

		if (ground_wall == false)
		{

			iColor = 0xff00ffff;
			if (ceiling_wall == false)
			{
				iPos.y += m_Velocity.y + (item_fall * Ga);
			}else 
			{
				iPos.y += (item_fall * Ga);
			}
		}
		else
		{
			m_ItemState = ITEM_STATE::PLACE;
			iColor = 0xffffffff;
		}

		if (ceiling_wall == false && left_right_wall == false && ground_wall == false)
		{
			iPos.x += m_Velocity.x;
		}else
			ceiling_wall = true;
		Ga += 0.981;
}


