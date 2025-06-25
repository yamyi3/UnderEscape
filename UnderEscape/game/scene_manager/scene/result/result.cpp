#include "result.h"
#include"vivid.h"
#include"../../scene_manager.h" 
#include"../gamemain/gamemain.h"
ResultScene::ResultScene()
:defult_color	(0xffffffff)
,left_right		(false)
,cursor_pos		(180.0f,776.0f)
,left_pos		(200.0f,800.0f)
,right_pos		(1370.0f,800.0f)
,result_pos		(180.0f,776.0f)
{
}

void ResultScene::Initialize()
{
}

void ResultScene::cursor_move()
{
	vivid::DrawTexture("data\\カーソル.jpg", cursor_pos, defult_color);
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

}

bool ResultScene::GetCursor()
{
	return left_right;
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

