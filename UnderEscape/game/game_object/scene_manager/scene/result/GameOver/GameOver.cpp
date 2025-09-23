#include "GameOver.h"
#include"../../../scene_manager.h" 
GameOver::GameOver()
{

}
void  GameOver::Initialize()
{

}

void  GameOver::Update()
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
void  GameOver::Draw()
{
	
	vivid::DrawTexture("data\\文字関係\\ゲームオーバー背景.png", vivid::Vector2(0.0f, 0.0f), 0xffffffff);
	vivid::DrawTexture("data\\文字関係\\GAMEOVER.png", result_pos, 0xffffffff);
	vivid::DrawTexture("data\\文字関係\\オーバーリトライ.png", menu_pos[0], 0xffffffff);
	vivid::DrawTexture("data\\文字関係\\オーバータイトルへ戻る.png", menu_pos[1], 0xffffffff);
	vivid::DrawTexture("data\\文字関係\\ゲームオーバーカーソル.png", cursor_pos, 0xffffffff);
}

void  GameOver::Finalize()
{
}

void GameOver::Scene()
{
	switch (picture)
	{
	case GameOverScene::Title:		//タイトル
		SceneManager::GetInstance().ChangeScene(SCENE_ID::TITLE);
		break;
	case GameOverScene::Retry:		//リトライ
		SceneManager::GetInstance().ChangeScene(SCENE_ID::GAMEMAIN);
		break;
	default:
		break;
	}
}
