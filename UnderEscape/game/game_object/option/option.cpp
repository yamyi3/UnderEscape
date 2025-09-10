#include "option.h"
#include "../game_object.h"

const int COption::m_MaxVolume = 100;
const int COption::m_FontSize = 40;
const float	COption::m_FrameWidth = 500.0f;
const float	COption::m_FrameHeight = 250.0f;

COption& COption::GetInstance(void)
{
	static COption instance;

	return instance;
}

void COption::Initialize(void)
{
	m_ButtonCount = 0;
	option_list = OPTION_LIST::CONTROLL;
	m_OptionMenu = false;
	m_SEMenu = false;
	m_BGMMenu = false;
	m_TriggerAButton = false;

	for (int i = 0; i < 3; i++)
	{
		m_MenuPos[i].x = m_FramePos.x + ((float)m_FontSize * 2);
		m_MenuPos[i].y = m_FramePos.y + (float)(i * m_FontSize + 40);
		m_MenuColor[i] = m_ColorList[0];
		m_VolumeColor[i] = m_ColorList[0];
		if (i == 0)
		{
			m_MenuColor[i] = m_ColorList[2];
			m_VolumeColor[i] = m_ColorList[2];
		}
	}
}
void COption::Update(void)
{
	namespace controller = vivid::controller;

	if (m_SoundMenu == false && m_ControllerMenu == false)
	{
		if (controller::Trigger(controller::DEVICE_ID::PLAYER1, controller::BUTTON_ID::A) && m_TriggerAButton == false)
		{
			m_TriggerAButton = true;

			switch (m_MenuCursor)
			{
			case 0:
				ControllerMenu();
				break;
			case 1:
				m_SoundMenu = true;
				break;
			case 2:
				m_OptionMenu = false;
				for (int i = 0; i < 3; ++i)
				{
					m_MenuColor[i] = m_ColorList[0];
					if (i == 0)
					{
						m_MenuColor[i] = m_ColorList[2];
					}
				}
				m_MenuCursor = 0;
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
	if (m_SoundMenu == true)
	{
		SoundMenu();
	}
	m_TriggerAButton = false;
}

void COption::Draw(void)
{
	vivid::DrawTexture("data\\menu_box.png", m_FramePos);
	for (int i = 0; i < 3; ++i)
	{
		vivid::DrawText(m_FontSize, m_MenuList[i], m_MenuPos[i], m_MenuColor[i]);
	}

	if (m_SoundMenu == true)
	{
		DrawSoundMenu();
	}
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
	if (vivid::controller::Trigger(vivid::controller::DEVICE_ID::PLAYER1, vivid::controller::BUTTON_ID::A) && m_TriggerAButton == false)
	{
		m_TriggerAButton = true;
		m_ControllerMenu = false;
	}
}

//サウンドメニューの動作
void COption::SoundMenu(void)
{
	namespace controller = vivid::controller;

	if (m_BGMMenu == false && m_SEMenu == false)
	{

		if (controller::Trigger(controller::DEVICE_ID::PLAYER1, controller::BUTTON_ID::A) && m_TriggerAButton == false)
		{
			m_TriggerAButton = true;

			switch (m_SoundMenuCursor)
			{
			case 0:
				if (m_SEMenu == false)
				{
					m_BGMMenu = true;
					m_VolumeColor[m_SoundMenuCursor] = m_ColorList[1];
				}
				break;
			case 1:
				if (m_BGMMenu == false)
				{
					m_SEMenu = true;
					m_VolumeColor[m_SoundMenuCursor] = m_ColorList[1];
				}
				break;
			case 2:
				
				for (int i = 0; i < 3; ++i)
				{
					m_VolumeColor[i] = m_ColorList[0];
					if (i == 0)
					{
						m_VolumeColor[i] = m_ColorList[2];
					}
				}
				m_SoundMenuCursor = 0;
				m_SoundMenu = false;
				break;
			}
		}

		//十字キー上を押したらメニューの選択カーソルがひとつ上に移動する(一番上の場合はその場を維持)
		if (controller::Trigger(controller::DEVICE_ID::PLAYER1, controller::BUTTON_ID::UP))
		{
			if (m_SoundMenuCursor > 0)
			{
				m_VolumeColor[m_SoundMenuCursor] = m_ColorList[0];
				m_SoundMenuCursor -= 1;
				m_VolumeColor[m_SoundMenuCursor] = m_ColorList[2];
			}
		}

		//十字キー下を押したらメニューの選択カーソルがひとつ下に移動する(一番下の場合はその場を維持)
		if (controller::Trigger(controller::DEVICE_ID::PLAYER1, controller::BUTTON_ID::DOWN))
		{
			if (0 <= m_SoundMenuCursor && m_SoundMenuCursor < 2)
			{
				m_VolumeColor[m_SoundMenuCursor] = m_ColorList[0];
				m_SoundMenuCursor += 1;
				m_VolumeColor[m_SoundMenuCursor] = m_ColorList[2];
			}
		}
	}

	if (m_BGMMenu == true)
	{
		ChangeSound(0);
	}
	if (m_SEMenu == true)
	{
		ChangeSound(1);
	}
}

//音量を調整する
void COption::ChangeSound(int cursor)
{
	namespace controller = vivid::controller;

	if (controller::Button(controller::DEVICE_ID::PLAYER1, controller::BUTTON_ID::RIGHT))
	{
		if (m_Volume[cursor] < 100 && m_ButtonCount == 0)
		{
			m_Volume[cursor]++;
		}
		m_ButtonCount++;
		if (m_ButtonCount >= 60)
		{
			if (m_ButtonCount % 5  == 0)
			{
				if (m_Volume[cursor] < 100)
				{
					m_Volume[cursor]++;
				};
			}
		}
	}

	if (controller::Released(controller::DEVICE_ID::PLAYER1, controller::BUTTON_ID::RIGHT))
	{
		m_ButtonCount = 0;
	}

	if (controller::Button(controller::DEVICE_ID::PLAYER1, controller::BUTTON_ID::LEFT))
	{
		if (m_Volume[cursor] > 0 && m_ButtonCount == 0)
		{
			m_Volume[cursor]--;
		}
		m_ButtonCount++;
		if (m_ButtonCount >= 60)
		{
			if (m_ButtonCount % 5 == 0)
			{
				if (m_Volume[cursor] > 0)
				{
					m_Volume[cursor]--;
				}
			}
		}
	}

	if (controller::Released(controller::DEVICE_ID::PLAYER1, controller::BUTTON_ID::LEFT))
	{
		m_ButtonCount = 0;
	}

	if (controller::Trigger(controller::DEVICE_ID::PLAYER1, controller::BUTTON_ID::B))
	{
		switch (cursor)
		{
		case 0:
			m_BGMMenu = false;
			break;
		case 1:
			m_SEMenu = false;
			break;
		}
		m_VolumeColor[cursor] = m_ColorList[2];
	}
}

void COption::DrawSoundMenu(void)
{
	vivid::DrawTexture("data\\menu_box.png", m_FramePos);
	for (int i = 0; i < 3; ++i)
	{
		if (i < 2)
		{
			vivid::DrawText(m_FontSize, m_VolumeMenuList[i] + "\t" + std::to_string(m_Volume[i]), m_MenuPos[i], m_VolumeColor[i]);
		}
		else
		{
			vivid::DrawText(m_FontSize, m_VolumeMenuList[i], m_MenuPos[i], m_VolumeColor[i]);
		}
	}
}

void COption::StartOption(void)
{
	m_OptionMenu = true;
}

void COption::EndOption(void)
{
	m_OptionMenu = false;
	m_SoundMenu = false;
	for (int i = 0; i < 3; ++i)
	{
		m_MenuColor[i] = m_ColorList[0];
		m_VolumeColor[i] = m_ColorList[0];
		if (i == 0)
		{
			m_MenuColor[i] = m_ColorList[2];
			m_VolumeColor[i] = m_ColorList[2];
		}
	}
	m_MenuCursor = 0;
	m_SoundMenuCursor = 0;

	m_BGMMenu = false;
	m_SEMenu = false;
}

COption::COption(void)
	: m_Volume{100, 100}
	, m_OptionMenu(false)
	, m_FramePos(((vivid::WINDOW_WIDTH / 2.0f) - (m_FrameWidth / 2.0f)),((vivid::WINDOW_HEIGHT / 2.0f) - (m_FrameHeight / 2.0f)) )
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