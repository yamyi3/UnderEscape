#include "result.h"
#include"vivid.h"
#include"../../scene_manager.h" 
#include"../gamemain/gamemain.h"
ResultScene::ResultScene()
:defult_color	(0xffffffff)
,left_right		(false)
,cursor_pos		(180.0f,776.0f)
, menu_pos{ vivid::Vector2(((float)vivid::WINDOW_WIDTH / 2.0f - 250.0f), ((float)vivid::WINDOW_HEIGHT - 400.0f)),vivid::Vector2(((float)vivid::WINDOW_WIDTH / 2.0f + 250.0f), ((float)vivid::WINDOW_HEIGHT - 400.0f)) }
,result_pos		(180.0f,776.0f)
{
}

void ResultScene::Initialize()
{
}

void ResultScene::CursorMove()
{
	namespace controller = vivid::controller;
	//vivid::DrawTexture("data\\カーソル.jpg", cursor_pos, defult_color);
	if (vivid::keyboard::Trigger(vivid::keyboard::KEY_ID::RIGHT))
	{
		left_right = true;
		cursor_pos.x = 1350.0f;
	};
	if (vivid::keyboard::Trigger(vivid::keyboard::KEY_ID::LEFT))
	{
		left_right = false;
		cursor_pos.x = 180.0f;
	};

	if(controller::Trigger(controller::DEVICE_ID::PLAYER1, controller::BUTTON_ID::RIGHT))
	{
		left_right = true;
	}
	if(controller::Trigger(controller::DEVICE_ID::PLAYER1, controller::BUTTON_ID::LEFT))
	{
		left_right = false;
	}
	cursor_pos = menu_pos[left_right];
}

bool ResultScene::GetCursor()
{
	return left_right;
}

void ResultScene::DrawCursor()
{
	vivid::DrawTexture("data\\ball.png", cursor_pos, 0xffffffff);
}

void ResultScene::Update()
{
	//switch (GameMainScene.GameFlg())
	//{
	//case true://クリア画面
	//	SceneManager::GetInstance().ChangeScene(SCENE_ID::GAMECLEAR);
	//	break;
	//case false://ゲームオーバー画面
	//	SceneManager::GetInstance().ChangeScene(SCENE_ID::GAMEOVER);
	//	break;
	//default:
	//	break;
	//}

	/*if (vivid::keyboard::Trigger(vivid::keyboard::KEY_ID::RETURN))
		SceneManager::GetInstance().ChangeScene(SCENE_ID::TITLE);*/
}

void ResultScene::Draw()
{
#ifdef  _DEBUG
	vivid::DrawText(40, "ResultScene", vivid::Vector2(0.0f, 0.0f), 0xffffffff);
	//vivid::DrawText(40, "Result Scene", vivid::Vector2(0.0f, 0.0f));
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

