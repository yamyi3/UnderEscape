#include "result.h"
#include"vivid.h"
#include"../../scene_manager.h" 
#include"../gamemain/gamemain.h"
ResultScene::ResultScene()
:defult_color	(0xffffffff)
,left_right		(false)

, menu_pos{ vivid::Vector2(((float)vivid::WINDOW_WIDTH / 2.0f - 600.0f), ((float)vivid::WINDOW_HEIGHT - 500.0f)),vivid::Vector2(((float)vivid::WINDOW_WIDTH / 2.0f), ((float)vivid::WINDOW_HEIGHT - 510.0f)) }
, cursor_pos(vivid::Vector2(0.0f, (vivid::WINDOW_HEIGHT - 420.0f)))
,result_pos		(vivid::Vector2(((vivid::WINDOW_WIDTH - 1033) / 2.0f), ((vivid::WINDOW_HEIGHT - 329) / 2.0f - 150.0f)))
{
}

void ResultScene::Initialize()
{
}

void ResultScene::CursorMove()
{
	namespace controller = vivid::controller;
	if (vivid::keyboard::Trigger(vivid::keyboard::KEY_ID::RIGHT))
	{
		left_right = true;
		cursor_pos.x = menu_pos[0].x - 55;
	};
	if (vivid::keyboard::Trigger(vivid::keyboard::KEY_ID::LEFT))
	{
		left_right = false;
		cursor_pos.x = menu_pos[1].x - 55;
	};

	if(controller::Trigger(controller::DEVICE_ID::PLAYER1, controller::BUTTON_ID::RIGHT))
	{
		left_right = true;
	}
	if(controller::Trigger(controller::DEVICE_ID::PLAYER1, controller::BUTTON_ID::LEFT))
	{
		left_right = false;
	}
	cursor_pos.x = menu_pos[left_right].x;
}

bool ResultScene::GetCursor()
{
	return left_right;
}

void ResultScene::Update()
{
}

void ResultScene::Draw()
{
#ifdef  _DEBUG
	vivid::DrawText(40, "ResultScene", vivid::Vector2(0.0f, 0.0f), 0xffffffff);
#endif 

}

void ResultScene::Finalize()
{
}

void ResultScene::Update(bool gFlg)
{
	switch (gFlg)
	{
	case true://クリア画面
		SceneManager::GetInstance().ChangeScene(SCENE_ID::GAMECLEAR);
		break;
	case false://ゲームオーバー画面
		SceneManager::GetInstance().ChangeScene(SCENE_ID::GAMEOVER);
		break;
	default:
		break;
	}
}

