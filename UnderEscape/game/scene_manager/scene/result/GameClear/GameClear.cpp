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
//描画
void GameClear::Draw()
{
	cursor_move();
	vivid::DrawTexture("data\\ステージクリア.webp",result_pos, defult_color);	//ロゴ
	vivid::DrawTexture("data\\次のステージへ.webp", left_pos, defult_color);	//左の選択
	vivid::DrawTexture("data\\タイトルにもどる.webp",right_pos, defult_color);	//右の選択
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
