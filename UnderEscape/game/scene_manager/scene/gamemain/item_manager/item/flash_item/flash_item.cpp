#include "flash_item.h"
const float CFlashItem::m_height = 32.0f;
const float CFlashItem::m_width = 32.0f;
const int CFlashItem::m_max_time = 50;
const int CFlashItem::m_number_of_times = 3;
const float CFlashItem::m_effect_area = 300.0f;
const float CFlashItem::m_radius = 16.0f;



CFlashItem::CFlashItem()
	: CItem(ITEM_ID::FLASH_ITEM, ITEM_STATE::PLACE, m_width, m_height, m_radius, m_effect_area, m_number_of_times)

	, m_X_Speed(30.0f) //�򋗗��̃}�C�i�X�{��(X��)�l������������Ɣ򋗗����L�т�
	, m_Y_Speed(30.0f) //�򋗗��̃}�C�i�X�{��(Y��)�l������������Ɣ򋗗����L�т�
	, m_Mouse_Pos(0.0f, 0.0f)

{
}

CFlashItem::~CFlashItem()
{
}

void CFlashItem::Initialize(vivid::Vector2 position)
{
	m_Position.x = position.x - m_width;
	m_Position.y = position.y - m_height;
	m_Color = m_default_color;
	m_Center.x = (m_Position.x + m_width) / 2;
	m_Center.y = (m_Position.y + m_height) / 2;

}


void CFlashItem::Draw(void)
{

	vivid::DrawTexture("data\\ball.png", m_Position - Character::GetInstance().GetScroll(), m_Color);

	vivid::DrawText(40, "rest�F" + std::to_string(m_Number_Of_Times + 1), vivid::Vector2(m_Position.x - (Character::GetInstance().GetScroll().x + 100.0f), m_Position.y - (Character::GetInstance().GetScroll().y + 100.0f)), 0xff00ffff);
	if (m_ItemState == ITEM_STATE::GET)
	{
		vivid::DrawTexture("data\\ball.png", m_Falling_Point - Character::GetInstance().GetScroll(), m_Effect_Color, vivid::Rect{ 0,0,(int)m_Width,(int)m_Height }, vivid::Vector2{ m_Radius,m_Radius }, vivid::Vector2{ m_Effect_Area / m_Width,m_Effect_Area / m_Height });

		for (int i = 0; i < 10; i++)
			vivid::DrawTexture("data\\ball.png", m_Orbit_Position[i] - Character::GetInstance().GetScroll(), m_Effect_Color);

	}

	if (m_Active == true)
	{
		vivid::DrawTexture("data\\ball.png", m_Position - Character::GetInstance().GetScroll(), m_Effect_Color, vivid::Rect{ 0,0,(int)m_Width,(int)m_Height }, vivid::Vector2{ m_Radius,m_Radius }, vivid::Vector2{ m_Effect_Area / m_Width,m_Effect_Area / m_Height });
	}


}



void CFlashItem::GetMove(vivid::Vector2 c_pos, float c_width, float c_height)
{
	m_Mouse_Pos.x = (vivid::mouse::GetCursorPos().x) + Character::GetInstance().GetScroll().x - c_pos.x;
	m_Mouse_Pos.y = c_pos.y - (vivid::mouse::GetCursorPos().y + Character::GetInstance().GetScroll().y);

	if (m_CatchFlg == true && vivid::keyboard::Trigger(vivid::keyboard::KEY_ID::C))
	{
		m_ItemState = ITEM_STATE::USE;
	}

	if (m_CatchFlg)
	{
		m_Position.x = c_pos.x + c_width;
		m_Position.y = c_pos.y + (c_height / 2);
		m_Center.x = (m_Position.x + m_width) / 2;
		m_Center.y = (m_Position.y + m_height) / 2;
		m_Color = m_picked_up_color;
	}
	m_Ga = 1.0;
	m_Velocity = vivid::Vector2(0.0f, 0.0f); // �d�͉����x�����Z�b�g
}

void CFlashItem::UseMove()
{

	//�A�C�e���I�u�W�F�N�g�̍��W�X�V

//catchFlg = false;


	m_Velocity.y = -(m_Mouse_Pos.y / m_Y_Speed);
	m_Velocity.x = (m_Mouse_Pos.x / m_X_Speed);
	//�ǂɐG�ꂽ�炻�̏�Ŏ��R����


	if (ground_wall == false)
	{

		m_Color = m_throw_color;
		if (ceiling_wall == false)
		{
			m_Position.y += m_Velocity.y + (m_Fall * m_Ga);
		}
		else
		{
			m_Position.y += (m_Fall * m_Ga);
		}
	}
	else
	{
		m_Active = true;
		if (m_Active_Time++ > m_max_time)
		{
			m_ItemState = ITEM_STATE::PLACE;

			m_Active_Time = 0;
			m_Active = false;
			m_Color = m_default_color;
			m_CatchFlg = false;
		}
	}


	if (ceiling_wall == false && left_right_wall == false && ground_wall == false)
	{
		m_Position.x += m_Velocity.x;
	}
	else
		ceiling_wall = true;
	m_Ga += 0.981;


}

void CFlashItem::SetOrbitPosition(vivid::Vector2 position, vivid::Vector2 c_pos)
{
	m_Orbit_Position[0] = m_Position;
	vivid::Vector2 save_position = m_Position;
	bool fall = false;
	for (int i = 1; i < 100; ++i)
	{
		m_Ga += 0.981;
		m_Velocity.y = -(m_Mouse_Pos.y / m_Y_Speed);
		m_Velocity.x = (m_Mouse_Pos.x / m_X_Speed);
		//�ǂɐG�ꂽ�炻�̏�Ŏ��R����


		save_position.y += m_Velocity.y + (m_Fall * m_Ga);
		save_position.x += m_Velocity.x;


		if (i % 10 == 0)
		{
			if (fall)
				m_Orbit_Position[i / 10] = m_Falling_Point;
			else
				m_Orbit_Position[i / 10] = save_position;
		}



		if (Stage::GetInstance().GetRoundHeight(save_position, m_Width, m_Height) - m_Height < save_position.y && fall == false)
		{
			fall = true;
			m_Falling_Point.y = Stage::GetInstance().GetRoundHeight(save_position, m_Width, m_Height) - m_Height;
			m_Falling_Point.x = save_position.x;
		}

	}
	m_Ga = 1.0;


}

