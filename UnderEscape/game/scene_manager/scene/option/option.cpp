#include "option.h"
#include "../../../game_object/game_object.h"

const int COption::m_MaxVolume = 100;
const int COption::m_FontSize = 40;

COption& COption::GetInstance(void)
{
	static COption instance;

	return instance;
}

void COption::Initialize(void)
{
	option_list = OPTION_LIST::CONTROLL;
	m_Volume[0] = 100;
	m_Volume[1] = 100;
}
void COption::Update(void)
{
	namespace controller = vivid::controller;

	if (controller::Trigger(controller::DEVICE_ID::PLAYER1, controller::BUTTON_ID::A))
	{
		m_MenuColor[m_MenuCursor] = m_ColorList[1];

		switch (m_MenuCursor)
		{
		case 0:
			ControllerMenu();
			break;
		case 1:
			SoundMenu();
			break;
		case 2:
			break;
		}
	}

	//十字キー上を押したらメニューの選択カーソルがひとつ上に移動する(一番上の場合はその場を維持)
	if (controller::Trigger(controller::DEVICE_ID::PLAYER1, controller::BUTTON_ID::UP))
	{
		if (m_MenuCursor > 0)
		{
			m_MenuColor[m_MenuCursor] = m_ColorList[0];
			m_MenuCursor -= 1;
			m_MenuColor[m_MenuCursor] = m_ColorList[2];
		}
	}

	//十字キー下を押したらメニューの選択カーソルがひとつ下に移動する(一番下の場合はその場を維持)
	if (controller::Trigger(controller::DEVICE_ID::PLAYER1, controller::BUTTON_ID::DOWN))
	{
		if (0 <= m_MenuCursor && m_MenuCursor < 2)
		{
			m_MenuColor[m_MenuCursor] = m_ColorList[0];
			m_MenuCursor += 1;
			m_MenuColor[m_MenuCursor] = m_ColorList[2];
		}
	}
}

void COption::Draw(void)
{
}

void COption::Finalize(void)
{
}

void COption::ChangeVolume(void)
{
}

void COption::SetVolume(void)
{
}

void COption::ControllerMenu(void)
{
	//vivid::DrawTexture("data\\menu_box.png", vivid::Vector2(500, 500));
}

void COption::SoundMenu(void)
{
	namespace controller = vivid::controller;

}

COption::COption(void)
{
}

COption::~COption(void)
{
}

COption::COption(const COption& rhs)
{
	(void)rhs;
}

COption& COption::operator = (const COption& rhs)
{
	(void)rhs;

	return *this;
}