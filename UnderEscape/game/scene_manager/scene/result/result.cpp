#include "result.h"
#include"vivid.h"
#include"../../scene_manager.h" 
#include"../gamemain/gamemain.h"
ResultScene::ResultScene()
{
	pos1 = { 200.0f,800.0f };
	pos2 = { 1370.0f,800.0f };
	pos3 = { 270.0f,0.0f };
	Cpos = { 180.0f,776.0f };
	color = 0xffffffff;
	Right = false;
}

void ResultScene::Initialize()
{

}

void ResultScene::cursor_move()
{
	vivid::DrawTexture("data\\カーソル.jpg", Cpos, color);
	if (vivid::keyboard::Trigger(vivid::keyboard::KEY_ID::RIGHT))
	{
		Right = true;
		Cpos.x = 1350.0f;
	};
	if (vivid::keyboard::Trigger(vivid::keyboard::KEY_ID::LEFT))
	{
		Right = false;
		Cpos.x = 180.0f;
	};

}

bool ResultScene::GetCursor()
{
	return Right;
}




void ResultScene::Update()
{
	switch (GamemainScene::GamemainScene().GameFlg())
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

	/*if (vivid::keyboard::Trigger(vivid::keyboard::KEY_ID::RETURN))
		SceneManager::GetInstance().ChangeScene(SCENE_ID::TITLE);*/
}

void ResultScene::Draw()
{
#ifdef  _DEBUG
	//vivid::DrawText(40, "Result Scene", vivid::Vector2(0.0f, 0.0f));
#endif 

}

void ResultScene::Finalize()
{
}

