#include "GameClear.h"
#include"../../../scene_manager.h" 
GameClear::GameClear()
{

}
void GameClear::Initialize()
{

}

void GameClear::Update()
{
	namespace controller = vivid::controller;
	CursorMove();

	if (controller::Trigger(controller::DEVICE_ID::PLAYER1, controller::BUTTON_ID::A))
	{
		switch (left_right)
		{
		case false:
			SceneManager::GetInstance().ChangeScene(SCENE_ID::GAMEMAIN);

			break;
		case true:
			SceneManager::GetInstance().ChangeScene(SCENE_ID::TITLE);
			break;
		}
	}
}
//描画
void GameClear::Draw()
{
	vivid::DrawTexture("data\\文字関係\\ゲームクリア背景.png", vivid::Vector2(0.0f, 0.0f), 0xffffffff);
	vivid::DrawTexture("data\\文字関係\\GAMECLEAR.png", result_pos, 0xffffffff);
	vivid::DrawTexture("data\\文字関係\\クリア後リトライ.png", menu_pos[0], 0xffffffff);
	vivid::DrawTexture("data\\文字関係\\クリア後タイトルへ戻る.png", menu_pos[1], 0xffffffff);
	vivid::DrawTexture("data\\文字関係\\カーソル.png", cursor_pos, 0xffffff00);
}

void GameClear::Finalize()
{
}

void GameClear::Scene()
{
	switch (picture)
	{
	case GameClearScene::Title:			//タイトル
		SceneManager::GetInstance().ChangeScene(SCENE_ID::TITLE);
		break;
	case GameClearScene::Next_Stage:		//次のステージへ
		SceneManager::GetInstance().ChangeScene(SCENE_ID::GAMEMAIN);
		break;
	default:
		break;
	}
}
