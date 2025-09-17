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

void  GameOver::Draw()
{
	//vivid::DrawTexture("data\\ゲームオーバー.jpg", result_pos, defult_color);		//ロゴ
	//vivid::DrawTexture("data\\やりなおす1.webp", left_pos, defult_color);			//左の選択
	//vivid::DrawTexture("data\\タイトルにもどる.webp", right_pos, defult_color);		//右の選択
//#ifdef _DEBUG
	DrawCursor();
	vivid::DrawText(40, "GameOverScene", vivid::Vector2(0.0f, 0.0f), 0xffffffff);
	vivid::DrawText(40, "GAMEOVER", (result_pos - vivid::Vector2(-300, 200)), defult_color);
	vivid::DrawText(40, "やりなおし", menu_pos[0],  defult_color);
	vivid::DrawText(40, "タイトルへ", (menu_pos[1]),  defult_color);
//#endif
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
