#include "sound_item.h"
#include "../../game/game_object/game_object.h"

const float CSoundItem::m_height = 32.0f;
const float CSoundItem::m_width = 32.0f;
const float CSoundItem::m_radius = 16.0f;
const float CSoundItem::m_effect_area = 500.0f;
const int CSoundItem::m_max_time = 10;
const int CSoundItem::m_number_of_times = 3;

CSoundItem::CSoundItem()
	: CItem(ITEM_ID::SOUND_ITEM, ITEM_STATE::PLACE, m_width, m_height, m_radius, m_effect_area, m_number_of_times)

	, m_X_Speed(10.0f) //飛距離のマイナス倍率(X軸)値を小さくすると飛距離が伸びる
	, m_Y_Speed(15.0f) //飛距離のマイナス倍率(Y軸)値を小さくすると飛距離が伸びる
	, m_Mouse_Pos(0.0f, 0.0f)
	, m_KeepVector(0.0f, 0.0f)
	, SoundBom( "data\\ball.png")
{
}

CSoundItem::~CSoundItem()
{
}

void CSoundItem::Initialize(vivid::Vector2 position)
{
	m_Position.x = position.x - m_width;
	m_Position.y = position.y - m_height;
	m_Color = m_default_color;
	m_Center.x = (m_Position.x + m_width) / 2;
	m_Center.y = (m_Position.y + m_height) / 2;
	m_Effect_Scale = { m_Effect_Area / 32, m_Effect_Area / 32 };
}


void CSoundItem::Draw(void)
{
	vivid::DrawTexture(SoundBom, m_Position - Character::GetInstance().GetScroll(), m_Color);


	if (m_ItemState == ITEM_STATE::GET)
	{
		vivid::DrawTexture(SoundBom, m_Orbit_Position[9] - Character::GetInstance().GetScroll(), m_Effect_Color, vivid::Rect{ 0,0,(int)m_Width,(int)m_Height }, vivid::Vector2{ m_Radius,m_Radius }, vivid::Vector2{ m_Effect_Area / m_Width,m_Effect_Area / m_Height });

		for (int i = 0; i < 9; i++)
			vivid::DrawTexture(SoundBom, m_Orbit_Position[i] - Character::GetInstance().GetScroll(), m_Effect_Color);

	}

	if (m_Active == true)
	{
		vivid::DrawTexture(SoundBom, m_Position - Character::GetInstance().GetScroll(), m_Effect_Color, vivid::Rect{ 0,0,(int)m_Width,(int)m_Height }, vivid::Vector2{ m_Radius,m_Radius }, vivid::Vector2{ m_Effect_Area / m_Width,m_Effect_Area / m_Height });
	}
}




void CSoundItem::GetMove(vivid::Vector2 c_pos, float c_width, float c_height)
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
	m_Velocity = vivid::Vector2(0.0f, 0.0f); // 重力加速度をリセット
}

void CSoundItem::UseMove()
{

	//アイテムオブジェクトの座標更新

//catchFlg = false;

	m_Velocity.y = -(m_Mouse_Pos.y / m_Y_Speed);
	m_Velocity.x = (m_Mouse_Pos.x / m_X_Speed);
	//壁に触れたらその場で自由落下


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
void CSoundItem::SetOrbitPosition(vivid::Vector2 position, vivid::Vector2 c_pos)
{
	m_Orbit_Position[0] = m_Position;
	vivid::Vector2 save_position = m_Position;
	bool vertical_move = true;//たて
	bool beside_move = true;//横
	bool right_beside_move = true;
	bool left_beside_move = true;

	for (int i = 1; i < 100; ++i)
	{
		m_Ga += 0.981;
		m_Velocity.y = -(m_Mouse_Pos.y / m_Y_Speed);
		m_Velocity.x = (m_Mouse_Pos.x / m_X_Speed);
		//壁に触れたらその場で自由落下

		if (!beside_move)
		{
			if (!right_beside_move)
			{
				save_position.x = Stage::GetInstance().GetRWall(save_position, m_Width, m_Height);
			}
			if (!left_beside_move)
			{
				save_position.x = Stage::GetInstance().GetLWall(save_position, m_Width, m_Height);
			}
		}

		if (vertical_move)
		{
			save_position.y += m_Velocity.y + (m_Fall * m_Ga);
			if (beside_move)
			{
				save_position.x += m_Velocity.x;
			}

		}
		else
		{
			save_position.y = Stage::GetInstance().GetRoundHeight(save_position, m_Width, m_Height) - m_Height;
		}


		if (!GroundCheck(save_position))
		{
			vertical_move = false;
			if (!LeftWallCheck(save_position) || !RightWallCheck(save_position))
			{
				beside_move = false;
				if (!LeftWallCheck(save_position))
				{
					left_beside_move = false;
				}
				else
					right_beside_move = false;
			}
		}

		if (i % 10 == 0)
		{
			m_Orbit_Position[i / 10] = save_position;
		}
	}
	m_Ga = 1.0;
}



