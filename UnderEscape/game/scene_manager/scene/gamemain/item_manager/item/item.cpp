#include"item.h"

Item::Item( ItemID id, ITEM_STATE state,float width,float heght,float radius)
	: m_Width	(width)
	, m_Height	(heght)
	, m_Radius	(radius)
	, m_ItemID	(id)
	, m_Position(0.0f, 0.0f)
	, m_Velocity(0.0f, 0.0f)
	, m_Color	(0xffffffff)
	, m_Anchor	(vivid::Vector2((float)m_Width / 2.0f, (float)m_Height / 2.0f))
	, m_Rect	{ 0, 0, m_Width,m_Height }
	, m_Scale	(1.0f, 1.0f)
	, m_Rotation	(0.0f)
	, m_ActiveFlag	(true)
	, m_ItemState	(state)
	, catchFlg	(false) 
	, iPos		(0.0f, 0.0f) 
	, iCenter	(0.0f, 0.0f) 
	, item_fall	(1.0f) 
	, Ga		(1.0f)
	, ceiling_wall		(false)
	, left_right_wall	(false)
	, ground_wall		(false)
{
}

Item::~Item(void)
{
}

void Item::Initialize( const vivid::Vector2& position)
{
	iPos.x = position.x - m_Width;
	iPos.y = position.y - m_Height;
	iColor = 0xffffffff;
	iCenter.x = (iPos.x + m_Width) / 2;
	iCenter.y = (iPos.y + m_Height) / 2;
	m_ActiveFlag = true; 
}

void Item::Update(vivid::Vector2 cPos, float cWidth, float cHeight, float rHeight)
{
	

	switch (m_ItemState)
	{
	case ITEM_STATE::GET:	//アイテムが所持している状態
		GetMove(cPos, cWidth, cHeight);
		break;
	case ITEM_STATE::USE:	//アイテムが使用されている状態
		WallCheck();
		UseMove(cPos);
		break;
	case ITEM_STATE::PLACE:	//アイテムが置かれた状態
		CheckObject(cPos,cWidth,cHeight);
		break;
	}

	
}

void Item::Draw(void)
{
	vivid::DrawTexture("data\\ball.png", iPos - Character::GetInstance().GetScroll(), iColor);
}

void Item::Finalize(void)
{
}

vivid::Vector2 Item::GetPosition(void)
{
	return iPos;
}

void Item::SetPosition(const vivid::Vector2& position)
{
	iPos = position;
}

vivid::Vector2 Item::GetCenterPosition(void)
{
	return iPos + vivid::Vector2((float)m_Width / 2.0f, (float)m_Height /
		2.0f);
}

float Item::GetRadius(void)
{
	return m_Radius;
}

bool Item::GetActive(void)
{
	return m_ActiveFlag;
}

void Item::SetActive(bool active)
{
	m_ActiveFlag = active;
}

ItemID Item::GetBulletCategory(void)
{
	return m_ItemID;
}

void Item::WallCheck()
{
	//壁判定
	//地面判定
	if (Stage::GetInstance().GetRoundHeight(iPos, m_Width, m_Height) - m_Height <iPos.y )
	{
		iPos.y = Stage::GetInstance().GetRoundHeight(iPos, m_Width, m_Height) - m_Height;
		ground_wall = true;
	}
	//左壁判定
	if (Stage::GetInstance().GetLWall(iPos, m_Width, m_Height)> iPos.x)
	{
		iPos.x = Stage::GetInstance().GetLWall(iPos, m_Width, m_Height);
		left_right_wall = true;
	}
	//右壁判定
	if (Stage::GetInstance().GetRWall(iPos, m_Width, m_Height)-m_Width < iPos.x)
	{
		iPos.x = Stage::GetInstance().GetRWall(iPos, m_Width, m_Height) - m_Width;
		left_right_wall = true;
	}
	//天井判定
	if (Stage::GetInstance().GetCeiling(iPos, m_Width, m_Height) > iPos.y)
	{
		iPos.y = Stage::GetInstance().GetCeiling(iPos, m_Width, m_Height);
		ceiling_wall = true;
		Ga = 1.0f; //天井に当たったら重力加速度をリセット
	}
}

void Item::GetMove(vivid::Vector2 cPos, float cWidth, float cHeight)
{
	//Cキーでアイテムを使用状態にする
	if (catchFlg == true && vivid::keyboard::Trigger(vivid::keyboard::KEY_ID::C))
	{
		m_ItemState = ITEM_STATE::USE;
		catchFlg = false;
	}

	if (catchFlg)
	{
		iPos.x = cPos.x + cWidth;
		iPos.y = cPos.y + (cHeight / 2);
		iCenter.x = (iPos.x + m_Width) / 2;
		iCenter.y = (iPos.y + m_Height) / 2;
		iColor = 0xffff00ff;
	}
	Ga = 1.0;
	m_Velocity = vivid::Vector2(0.0f, 0.0f); // 重力加速度をリセット
}



void Item::UseMove( vivid::Vector2 c_pos)
{
	//アイテムオブジェクトの座標更新
	catchFlg = false;
	if (ground_wall == false)
	{
		iPos.x += 3;
		iPos.y +=  (item_fall * Ga);
		iColor = 0xff00ffff;
	}
	else
	{
		m_ItemState = ITEM_STATE::PLACE;
		iColor = 0xffffffff;
	}
	Ga += 0.981;
}

void Item::CheckObject(vivid::Vector2 cPos, float cWidth, float cHeight)//アイテムを持つ（当たり判定）
{
	if (cPos.x < iPos.x + m_Width && cPos.x + cWidth > iPos.x
		&& cPos.y < iPos.y + m_Height && cPos.y + cHeight > iPos.y)
	{
		if (vivid::keyboard::Trigger(vivid::keyboard::KEY_ID::F))
		{
			catchFlg		= true;
			ceiling_wall	= false;
			left_right_wall = false;
			ground_wall		= false;
			m_ItemState		= ITEM_STATE::GET;
		}
	}
}

