#include "flash_item.h"
#include "../../game/game_object/game_object.h"

const float CFlashItem::m_height = 80.0f;
const float CFlashItem::m_width = 73.0f;
const int CFlashItem::m_max_time = 50;
const int CFlashItem::m_number_of_times = 3;
const float CFlashItem::m_effect_area = 300.0f;
const float CFlashItem::m_radius = 16.0f;



CFlashItem::CFlashItem()
	: CItem(ITEM_ID::FLASH_ITEM, ITEM_STATE::PLACE, m_width, m_height, m_radius, m_effect_area, m_number_of_times)

	, m_X_Speed(10.0f) //�򋗗��̃}�C�i�X�{��(X��)�l������������Ɣ򋗗����L�т�
	, m_Y_Speed(15.0f) //�򋗗��̃}�C�i�X�{��(Y��)�l������������Ɣ򋗗����L�т�
	, m_Mouse_Pos(0.0f, 0.0f)
	, m_KeepVector(0.0f, 0.0f)

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

	vivid::DrawTexture("data\\�A�C�e��\\�M����.png", m_Position - Character::GetInstance().GetScroll(), m_Color);

	vivid::DrawText(40, "rest�F" + std::to_string(m_Number_Of_Times + 1), vivid::Vector2(m_Position.x - (Character::GetInstance().GetScroll().x + 100.0f), m_Position.y - (Character::GetInstance().GetScroll().y + 100.0f)), 0xff00ffff);
	if (m_ItemState == ITEM_STATE::GET)
	{
		vivid::DrawTexture("data\\�A�C�e��\\�M����.png", m_Orbit_Position[9], m_Effect_Color, vivid::Rect{ 0,0,(int)m_Width,(int)m_Height }, vivid::Vector2{ m_Radius,m_Radius }, vivid::Vector2{ m_Effect_Area / m_Width,m_Effect_Area / m_Height });

		for (int i = 0; i < 9; i++)
			vivid::DrawTexture("data\\�A�C�e��\\�M����.png", m_Orbit_Position[i] - Character::GetInstance().GetScroll(), m_Effect_Color);

	}

	if (m_Active == true)
	{
		vivid::DrawTexture("data\\�A�C�e��\\�M����.png", m_Position - Character::GetInstance().GetScroll(), m_Effect_Color, vivid::Rect{ 0,0,(int)m_Width,(int)m_Height }, vivid::Vector2{ m_Radius,m_Radius }, vivid::Vector2{ m_Effect_Area / m_Width,m_Effect_Area / m_Height });
	}
}

void CFlashItem::GetMove(vivid::Vector2 c_pos, float c_width, float c_height)
{
	m_Mouse_Pos = (Character::GetInstance().GetRightStick() * (vivid::Vector2(m_X_Speed, m_Y_Speed) + vivid::Vector2(300.0f, 300.0f)));

	if (m_CatchFlg == true && Character::GetInstance().GetTriggerLB())
	{
		m_ItemState = ITEM_STATE::USE;
		m_KeepVector = Character::GetInstance().GetRightStick();
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
		CItem::V_WallCheck();
	}
	else
	{
		m_Active = true;
		CItem::CheckActiveItem();
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
		CItem::H_WallCheck();
	}
	else
		ceiling_wall = true;
	m_Ga += 0.981;


}

void CFlashItem::SetOrbitPosition(vivid::Vector2 position, vivid::Vector2 c_pos)
{
	m_Orbit_Position[0] = m_Position;
	vivid::Vector2 save_position = m_Position;
	bool fall = true;

	for (int i = 1; i < 100; ++i)
	{
		m_Ga += 0.981;
		m_Velocity.y = -(m_Mouse_Pos.y / m_Y_Speed);
		m_Velocity.x = (m_Mouse_Pos.x / m_X_Speed);
		//�ǂɐG�ꂽ�炻�̏�Ŏ��R����
		if (CelingCheck(save_position))
			//fall = false;
		if (GroundCheck(save_position))
		{
			if (LeftWallCheck(save_position)&& RightWallCheck(save_position)&&fall)
			{
				save_position.x += m_Velocity.x;
			}
			save_position.y += m_Velocity.y + (m_Fall * m_Ga);
		}
		else
		{
			//for (;;)
			//{
			//	if (!LeftWallCheck(save_position))
			//	{
			//		save_position.x += 1.0f;
			//	}
			//	if (!RightWallCheck(save_position))
			//	{
			//		save_position.x -= 1.0f;
			//	}
			//	if (!GroundCheck(save_position))
			//	{
			//		save_position.y -= 1.0f;
			//	}
			//	if (LeftWallCheck(save_position) && RightWallCheck(save_position) && GroundCheck(save_position))
			//	{
			//		break;
			//	}
			//}
		}
		if (i % 10 == 0)
		{
				m_Orbit_Position[i / 10] = save_position;
		}
	}
	m_Ga = 1.0;
}

