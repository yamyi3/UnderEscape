#include"item.h"

Item::Item( ItemID id, ITEM_STATE state,float width,float heght,float radius)
	: m_Width(width)
	, m_Height(heght)
	, m_Radius(radius)
	, m_ItemID(id)
	, m_Position(0.0f, 0.0f)
	, m_Velocity(0.0f, 0.0f)
	, m_Color(0xffffffff)
	, m_Anchor(vivid::Vector2((float)m_Width / 2.0f, (float)m_Height / 2.0f))
	, m_Rect{ 0, 0, m_Width,m_Height }
	, m_Scale(1.0f, 1.0f)
	, m_Rotation(0.0f)
	, m_ActiveFlag(true)
	, m_ItemState(state)
	, catchFlg(false) 
	, iPos(0.0f, 0.0f) 
	, iCenter(0.0f, 0.0f) 
	, item_fall(1.0f) 
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
	case ITEM_STATE::GET:
		GetMove(cPos, cWidth, cHeight);
		break;
	case ITEM_STATE::USE:
		UseMove(rHeight, cPos);
		break;
	case ITEM_STATE::PLACE:
		CheckObject(cPos);
		//PutMove(rHeight);
		break;
	}

	
}

void Item::Draw(void)
{
	vivid::DrawTexture("data\\ball.png", iPos, iColor);
}

void Item::Finalize(void)
{
}

vivid::Vector2 Item::GetPosition(void)
{
	return m_Position;
}

void Item::SetPosition(const vivid::Vector2& position)
{
	m_Position = position;
}

vivid::Vector2 Item::GetCenterPosition(void)
{
	return m_Position + vivid::Vector2((float)m_Width / 2.0f, (float)m_Height /
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

void Item::GetMove(vivid::Vector2 cPos, float cWidth, float cHeight)
{
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
	V = 0.0;
}

void Item::PutMove(float rHeight)
{
	if (iPos.y + m_Height < rHeight)
		iPos.y += 7.5;
	else
	{
		iPos.y = rHeight - m_Height;
	}
	iColor = 0xffffffff;

}

void Item::UseMove(float rHeight, vivid::Vector2 c_pos)
{
	catchFlg = false;
	if (iPos.y + m_Height < rHeight)
	{
		iPos.x += 3;
		iPos.y +=  (item_fall * Ga);
		iColor = 0xff00ffff;
	}

	if (iPos.y + m_Height >= rHeight)
	{
		iPos.y = rHeight - m_Height;
		m_ItemState = ITEM_STATE::PLACE;
		iColor = 0xffffffff;
	}
	Ga += 0.981;
}

void Item::CheckObject(vivid::Vector2 cPos)//アイテムを持つ（当たり判定）
{
	//対角線とベクトルで処理を行う(単ブロックに使用推奨)  
	float a1 = -GetItemHeight() / GetItemWidth();
	float a2 = GetItemHeight() / GetItemWidth();
	float a3 = (getItemPos().y - GetItemCenter().y) / (cPos.x - getItemPos().x);

	if (cPos.x < getItemPos().x + GetItemWidth() && cPos.x + 72.0f > getItemPos().x
		&& cPos.y < getItemPos().y + GetItemHeight() && cPos.y + 180.0f > getItemPos().y)
	{
		if (vivid::keyboard::Trigger(vivid::keyboard::KEY_ID::F))
		{
			catchFlg = true;
			m_ItemState = ITEM_STATE::GET;
		}
	}
}

