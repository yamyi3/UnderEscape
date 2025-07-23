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
	, Ga(1.0f)
	, ceiling_wall(false)
	, left_right_wall(false)
	, ground_wall(false)
{
}

Item::~Item(void)
{
}

void Item::Initialize( const vivid::Vector2& position)
{
	iPos.x = position.x;
	iPos.y = position.y;
	iPos.y = Stage::GetInstance().GetRoundHeight(iPos, m_Width, m_Height)-m_Height;
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
		wallCheck();
		UseMove(cPos);
		break;
	case ITEM_STATE::PLACE:
		CheckObject(cPos,cWidth,cHeight);
		break;
	}

	
}

void Item::Draw(void)
{
	vivid::DrawTexture("data\\ball.png", iPos- Character::GetInstance().GetScroll(), iColor);
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

void Item::wallCheck()
{
	//�ǔ���
	//�n�ʔ���
	if (Stage::GetInstance().GetRoundHeight(iPos, m_Width, m_Height) - m_Height <iPos.y )
	{
		iPos.y = Stage::GetInstance().GetRoundHeight(iPos, m_Width, m_Height) - m_Height;
		ground_wall = true;
	}
	//���ǔ���
	if (Stage::GetInstance().GetLWall(iPos, m_Width, m_Height)> iPos.x)
	{
		iPos.x = Stage::GetInstance().GetLWall(iPos, m_Width, m_Height);
		left_right_wall = true;
	}
	//�E�ǔ���
	if (Stage::GetInstance().GetRWall(iPos, m_Width, m_Height)-m_Width < iPos.x)
	{
		iPos.x = Stage::GetInstance().GetRWall(iPos, m_Width, m_Height) - m_Width;
		left_right_wall = true;
	}
	//�V�䔻��
	if (Stage::GetInstance().GetCeiling(iPos, m_Width, m_Height) > iPos.y)
	{
		iPos.y = Stage::GetInstance().GetCeiling(iPos, m_Width, m_Height);
		ceiling_wall = true;
		Ga = 1.0f; //�V��ɓ���������d�͉����x�����Z�b�g
	}
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
	m_Velocity = vivid::Vector2(0.0f, 0.0f); // �d�͉����x�����Z�b�g
}



void Item::UseMove( vivid::Vector2 c_pos)
{
	catchFlg = false;
	if (iPos.y + m_Height <1)
	{
		iPos.x += 3;
		iPos.y +=  (item_fall * Ga);
		iColor = 0xff00ffff;
	}

	if (iPos.y + m_Height >= 1)
	{
		iPos.y = 1 - m_Height;
		m_ItemState = ITEM_STATE::PLACE;
		iColor = 0xffffffff;
	}
	Ga += 0.981;
}

void Item::CheckObject(vivid::Vector2 cPos, float cWidth, float cHeight)//�A�C�e�������i�����蔻��j
{

	if (cPos.x < iPos.x + m_Width && cPos.x + cWidth > iPos.x
		&& cPos.y < iPos.y + m_Height && cPos.y + cHeight > iPos.y)
	{
		if (vivid::keyboard::Trigger(vivid::keyboard::KEY_ID::F))
		{
			catchFlg = true;
			ceiling_wall = false;
			left_right_wall = false;
			ground_wall = false;
			m_ItemState = ITEM_STATE::GET;
		}
	}
}

