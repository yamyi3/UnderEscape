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
	if (GetCursor() == true && vivid::keyboard::Trigger(vivid::keyboard::KEY_ID::RETURN))
	{

		picture = GameOverScene::Title;
		GameOver::Scene();
	}
	if (GetCursor() == false && vivid::keyboard::Trigger(vivid::keyboard::KEY_ID::RETURN))
	{
		picture = GameOverScene::Retry;
		GameOver::Scene();
	}
}

void  GameOver::Draw()
{
	cursor_move();
	vivid::DrawTexture("data\\ゲームオーバー.jpg", pos3, color);
	vivid::DrawTexture("data\\やりなおす1.webp", pos1, color);
	vivid::DrawTexture("data\\タイトルにもどる.webp", pos2, color);

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
