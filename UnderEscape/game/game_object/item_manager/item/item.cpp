#include"item.h"

const unsigned int CItem::m_default_color = 0xffffffff;
const unsigned int CItem::m_can_pick_up_color = 0xff00ff00;
const unsigned int CItem::m_picked_up_color = 0xffff00ff;
const unsigned int CItem::m_throw_color = 0xff00ffff;


CItem::CItem(ITEM_ID id, ITEM_STATE state, float width, float heght, float radius, float effect_area, int number_of_times)
	: m_Width(width)
	, m_Height(heght)
	, m_Radius(radius)
	, m_ItemID(id)
	, m_Position(0.0f, 0.0f)
	, m_Velocity(0.0f, 0.0f)
	, m_Color(m_default_color)
	, m_Anchor(vivid::Vector2((float)m_Width / 2.0f, (float)m_Height / 2.0f))
	, m_Rect{ 0, 0, m_Width,m_Height }
	, m_Scale(1.0f, 1.0f)
	, m_Rotation(0.0f)
	, m_ActiveFlag(true)
	, m_ItemState(state)
	, m_CatchFlg(false)
	, m_Fall(1.0f)
	, m_Ga(1.0f)
	, ceiling_wall(false)
	, left_right_wall(false)
	, ground_wall(false)
	, m_Active(false)
	, m_Active_Time(0)
	, m_Effect_Area(effect_area)
	, m_Effect_Anchor(16.0f, 16.0f)
	, m_Effect_Scale(0, 0)
	, m_Effect_Color(0x55ffffff)
	, m_Effect_Rect{ 0,0,32,32 }
	, m_Number_Of_Times(number_of_times)
	, m_First(true)
	, m_Orbit_Position{ vivid::Vector2::ZERO }
	, m_Place_Flg(true)
{
}

CItem::~CItem(void)
{
}

void CItem::Initialize(const vivid::Vector2& position)
{
	m_Position.x = position.x - m_Width;
	m_Position.y = position.y - m_Height;
	m_Color = m_default_color;
	m_Center.x = (m_Position.x + m_Width) / 2;
	m_Center.y = (m_Position.y + m_Height) / 2;
	m_ActiveFlag = true;
	m_Effect_Scale = { m_Effect_Area / 32, m_Effect_Area / 32 };

}

void CItem::Update(vivid::Vector2 c_pos, float c_width, float c_height, float r_reight)
{


	switch (m_ItemState)
	{
	case ITEM_STATE::GET:	//アイテムが所持している状態
		GetMove(c_pos, c_width, c_height);
		//コメントアウトしないと軌道が画面外に行った時エラーが起きる
		SetOrbitPosition(m_Position, c_pos);
		break;
	case ITEM_STATE::USE:	//アイテムが使用されている状態
		WallCheck();
		UseMove();
		break;
	case ITEM_STATE::PLACE:	//アイテムが置かれた状態
		ItemPlace(c_pos);
		CheckObject(c_pos, c_width, c_height);
		break;
	}

	if (m_Number_Of_Times < 0)//使用回数を超えたら消去
	{
		Destroy();
	}

}

void CItem::Draw(void)
{
	vivid::DrawTexture("data\\ball.png", m_Position - Character::GetInstance().GetScroll(), m_Color);
	if (m_ItemState == ITEM_STATE::GET)
	{
		for (int i = 0; i < 10; i++)
			vivid::DrawTexture("data\\ball.png", m_Orbit_Position[i] - Character::GetInstance().GetScroll(), 0x66ffffff);
	}
}

void CItem::Finalize(void)
{
}

vivid::Vector2 CItem::GetPosition(void)
{
	return m_Position;
}

void CItem::SetPosition(const vivid::Vector2& position)
{
	m_Position = position;
}

vivid::Vector2 CItem::GetCenterPosition(void)
{
	return m_Position + vivid::Vector2((float)m_Width / 2.0f, (float)m_Height /
		2.0f);
}

float CItem::GetRadius(void)
{
	return m_Radius;
}

bool CItem::GetActive(void)
{
	return m_ActiveFlag;
}

void CItem::SetActive(bool active)
{
	m_ActiveFlag = active;
}

ITEM_ID CItem::GetBulletCategory(void)
{
	return m_ItemID;
}

void CItem::WallCheck()
{
	m_First = true;
	//壁判定
	//地面判定
	if (Stage::GetInstance().GetRoundHeight(m_Position, m_Width, m_Height) - m_Height < m_Position.y)
	{
		m_Position.y = Stage::GetInstance().GetRoundHeight(m_Position, m_Width, m_Height) - m_Height;
		ground_wall = true;
	}
	//左壁判定
	if (Stage::GetInstance().GetLWall(m_Position, m_Width, m_Height) > m_Position.x)
	{
		m_Position.x = Stage::GetInstance().GetLWall(m_Position, m_Width, m_Height);
		left_right_wall = true;
	}
	//右壁判定
	if (Stage::GetInstance().GetRWall(m_Position, m_Width, m_Height) - m_Width < m_Position.x)
	{
		m_Position.x = Stage::GetInstance().GetRWall(m_Position, m_Width, m_Height) - m_Width;
		left_right_wall = true;
	}
	//天井判定
	if (Stage::GetInstance().GetCeiling(m_Position, m_Width, m_Height) > m_Position.y)
	{
		m_Position.y = Stage::GetInstance().GetCeiling(m_Position, m_Width, m_Height);
		ceiling_wall = true;
		m_Ga = 1.0f; //天井に当たったら重力加速度をリセット
	}
}



void CItem::SetOrbitPosition(vivid::Vector2 position, vivid::Vector2 c_pos)
{
	m_Orbit_Position[0] = position;
	vivid::Vector2 save_position;
	for (int i = 1; i < 100; ++i)
	{
		save_position.x += 3;
		save_position.y += (m_Fall * m_Ga);
		m_Ga += 0.981;

		if (i % 10 == 0)
		{
			m_Orbit_Position[i / 10] = save_position + position;
		}
	}
	m_Ga = 1.0;

}

void CItem::Found(void)
{
	m_CatchFlg = true;
	ceiling_wall = false;
	left_right_wall = false;
	ground_wall = false;
	m_ItemState = ITEM_STATE::GET;
}

void CItem::Thrown(void)
{
	m_ItemState = ITEM_STATE::USE;
}

void CItem::Place(vivid::Vector2 c_pos)
{
	m_Position.x = c_pos.x;
	m_CatchFlg = false;
	m_Place_Flg = true;
	m_ItemState = ITEM_STATE::PLACE;
}

void CItem::ItemPlace(vivid::Vector2 c_pos)
{
	if (m_Place_Flg)
	{
		if (Stage::GetInstance().GetRoundHeight(m_Position, m_Width, m_Height) - m_Height < m_Position.y)
		{
			m_Position.y = Stage::GetInstance().GetRoundHeight(m_Position, m_Width, m_Height) - m_Height;
			m_Place_Flg = false;
			m_Color = m_default_color;
			m_Ga = 1.0;
		}
		else
		{
			m_Position.y += (m_Fall * m_Ga);
			m_Ga += 0.981;
		}
	}
}

bool CItem::GroundCheck(vivid::Vector2 position)
{
	//地面判定
	if (Stage::GetInstance().GetRoundHeight(position, m_Width, m_Height) - m_Height < position.y)
	{
		return false;
	}

		return true;
	
}

bool CItem::CelingCheck(vivid::Vector2 position)
{
	//天井判定
	if (Stage::GetInstance().GetCeiling(position, m_Width, m_Height) > m_Position.y)
	{
		return false;
	}

	return true;
}

bool CItem::LeftWallCheck(vivid::Vector2 position)
{
	//左壁判定
	if (Stage::GetInstance().GetLWall(position, m_Width, m_Height) > position.x)
	{
		return false;
	}

	return true;
}

bool CItem::RightWallCheck(vivid::Vector2 position)
{
	//右壁判定
	if (Stage::GetInstance().GetRWall(position, m_Width, m_Height) - m_Width < m_Position.x)
	{
		return false;
	}

	return true;
}

bool CItem::WallCheck(vivid::Vector2 position)
{
	//左壁判定
	if (Stage::GetInstance().GetLWall(position, m_Width, m_Height) > position.x)
	{
		return false;
	}
	//右壁判定
	if (Stage::GetInstance().GetRWall(position, m_Width, m_Height) - m_Width < m_Position.x)
	{
		return false;
	}
	//天井判定
	if (Stage::GetInstance().GetCeiling(position, m_Width, m_Height) > m_Position.y)
	{
			return false;
	}

	return true;
}

void CItem::GetMove(vivid::Vector2 c_pos, float c_width, float c_height)
{
	//Cキーでアイテムを使用状態にする
	if (m_CatchFlg == true && vivid::keyboard::Trigger(vivid::keyboard::KEY_ID::C))
	{
		m_ItemState = ITEM_STATE::USE;
	}
	if (m_CatchFlg == true && vivid::keyboard::Trigger(vivid::keyboard::KEY_ID::V))
	{
		m_ItemState = ITEM_STATE::USE;
	}


	if (m_CatchFlg)
	{
		m_Position.x = c_pos.x + c_width;
		m_Position.y = c_pos.y + (c_height / 2);
		m_Center.x = (m_Position.x + m_Width) / 2;
		m_Center.y = (m_Position.y + m_Height) / 2;
		m_Color = m_picked_up_color;
	}
	m_Ga = 1.0;
	m_Velocity = vivid::Vector2(0.0f, 0.0f); // 重力加速度をリセット
}



void CItem::UseMove()
{
	//アイテムオブジェクトの座標更新
	if (ground_wall == false)
	{
		m_Position.x += 3;
		m_Position.y += (m_Fall * m_Ga);
		m_Color = m_throw_color;
	}
	else
	{
		m_CatchFlg = false;
		m_ItemState = ITEM_STATE::PLACE;
		m_Color = m_default_color;
	}
	m_Ga += 0.981;
}

void CItem::CheckObject(vivid::Vector2 c_pos, float c_width, float c_height)//アイテムを持つ（当たり判定）
{
	if (m_First)
	{
		m_Number_Of_Times--;
		m_First = false;
	}
	if (c_pos.x < m_Position.x + m_Width && c_pos.x + c_width > m_Position.x
		&& c_pos.y < m_Position.y + m_Height && c_pos.y + c_height > m_Position.y)
	{
		m_Color = m_can_pick_up_color;


		//if (vivid::keyboard::Trigger(vivid::keyboard::KEY_ID::F)&&check==false&&priority==true)
		//{
		//	catchFlg		= true;
		//	ceiling_wall	= false;
		//	left_right_wall = false;
		//	ground_wall		= false;
		//	m_GetItemID		= m_ItemID;
		//	m_ItemState		= ITEM_STATE::GET;
		//	
		//}
	}
	else
		m_Color = m_default_color;

}

