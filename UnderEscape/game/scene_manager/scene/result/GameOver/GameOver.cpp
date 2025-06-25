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
	vivid::DrawTexture("data\\ゲームオーバー.jpg", result_pos, defult_color);		//ロゴ
	vivid::DrawTexture("data\\やりなおす1.webp", left_pos, defult_color);			//左の選択
	vivid::DrawTexture("data\\タイトルにもどる.webp", right_pos, defult_color);		//右の選択

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
