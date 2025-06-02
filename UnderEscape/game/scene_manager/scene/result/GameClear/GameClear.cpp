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
	if (GetCursor() == true && vivid::keyboard::Trigger(vivid::keyboard::KEY_ID::RETURN))
	{
		picture = GameClearScene::Title;
		GameClear::Scene();
	}
	if (GetCursor() == false && vivid::keyboard::Trigger(vivid::keyboard::KEY_ID::RETURN))
	{
		picture = GameClearScene::Next_Stage;
		GameClear::Scene();
	}
}

void GameClear::Draw()
{
	cursor_move();
	vivid::DrawTexture("data\\ステージクリア.webp", pos3, color);
	vivid::DrawTexture("data\\次のステージへ.webp", pos1, color);
	vivid::DrawTexture("data\\タイトルにもどる.webp", pos2, color);
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
