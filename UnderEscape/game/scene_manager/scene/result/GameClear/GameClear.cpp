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
	
	//vivid::DrawTexture("data\\ステージクリア.webp",result_pos, defult_color);	//ロゴ
	//vivid::DrawTexture("data\\次のステージへ.webp", left_pos, defult_color);	//左の選択
	//vivid::DrawTexture("data\\タイトルにもどる.webp",right_pos, defult_color);	//右の選択
#ifdef _DEBUG
	vivid::DrawText(40, "GameClearScene", vivid::Vector2(0.0f, 0.0f), 0xffffffff);
	vivid::DrawText(40, "がめこれあー", result_pos, defult_color);
	vivid::DrawText(40, "もっかい！", result_pos, defult_color);
	vivid::DrawText(40, "タイトール", result_pos, defult_color);
#endif
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
