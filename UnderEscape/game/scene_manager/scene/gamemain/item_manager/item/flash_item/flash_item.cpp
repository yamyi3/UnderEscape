#include "flash_item.h"
const float FlashItem::item_height = 32.0f;
const float FlashItem::item_width = 32.0f;
const float FlashItem::item_radius = 16.0f;
const int FlashItem::max_item_time = 50;
const int FlashItem::max_number_of_times = 3;



FlashItem::FlashItem()
	: Item(ITEM_ID::FLASH_ITEM, ITEM_STATE::PLACE, item_width, item_height, item_radius)

	, Xspeed(30.0f) //飛距離のマイナス倍率(X軸)値を小さくすると飛距離が伸びる
	, Yspeed(30.0f) //飛距離のマイナス倍率(Y軸)値を小さくすると飛距離が伸びる
	, Mouse(0.0f, 0.0f)

{
}

FlashItem::~FlashItem()
{
}

void FlashItem::Initialize(vivid::Vector2 position)
{
	iPos.x = position.x - item_width;
	iPos.y = position.y - item_height;
	iColor = 0xffffffff;
	iCenter.x = (iPos.x + item_width) / 2;
	iCenter.y = (iPos.y + item_height) / 2;
	m_Area = 300.0f;

}


void FlashItem::Draw(void)
{
	vivid::DrawTexture("data\\ball.png", iPos - Character::GetInstance().GetScroll(), iColor);

	if (m_Active == true)
	{
		vivid::DrawTexture("data\\ball.png", iPos - Character::GetInstance().GetScroll(), m_Effect_Color, vivid::Rect{ 0,0,32,32 }, vivid::Vector2{ 16.0f,16.0f }, vivid::Vector2{ 9.375f,9.375f });
	}
}



void FlashItem::GetMove(vivid::Vector2 cPos, float cWidth, float cHeight)
{
	if (catchFlg == true && vivid::keyboard::Trigger(vivid::keyboard::KEY_ID::C))
	{
		m_ItemState = ITEM_STATE::USE;
		//catchFlg = false;

		Mouse.x = (vivid::mouse::GetCursorPos().x) + Character::GetInstance().GetScroll().x - cPos.x;
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

void FlashItem::UseMove(vivid::Vector2 c_pos)
{
	//アイテムオブジェクトの座標更新

	//catchFlg = false;


	m_Velocity.y = -(Mouse.y / Yspeed);
	m_Velocity.x = (Mouse.x / Xspeed);
	//壁に触れたらその場で自由落下


	if (ground_wall == false)
	{

		iColor = 0xff00ffff;
		if (ceiling_wall == false)
		{
			iPos.y += m_Velocity.y + (item_fall * Ga);
		}
		else
		{
			iPos.y += (item_fall * Ga);
		}
	}
	else
	{
		m_Active = true;
		if (++item_active_time > max_item_time)
		{
			//--number_of_times;
			item_active_time = 0;
			m_Active = false;
			iColor = 0xffffffff;
			catchFlg = false;
			m_ItemState = ITEM_STATE::PLACE;

		}
	}


	if (ceiling_wall == false && left_right_wall == false && ground_wall == false)
	{
		iPos.x += m_Velocity.x;
	}
	else
		ceiling_wall = true;

	Ga += 0.981;
}


