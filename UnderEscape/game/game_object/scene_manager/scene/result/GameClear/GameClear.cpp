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
//�`��
void GameClear::Draw()
{
//#ifdef _DEBUG
	DrawCursor();
	vivid::DrawText(40, "GameClearScene", vivid::Vector2(0.0f, 0.0f), 0xffffffff);
	vivid::DrawText(40, "GAMECLEAR", (result_pos - vivid::Vector2(-300, 200)), defult_color);
	vivid::DrawText(40, "���g���C", menu_pos[0], defult_color);
	vivid::DrawText(40, "�^�C�g����", (menu_pos[1]), defult_color);
//#endif
}

void GameClear::Finalize()
{
}

void GameClear::Scene()
{
	switch (picture)
	{
	case GameClearScene::Title:			//�^�C�g��
		SceneManager::GetInstance().ChangeScene(SCENE_ID::TITLE);
		break;
	case GameClearScene::Next_Stage:		//���̃X�e�[�W��
		SceneManager::GetInstance().ChangeScene(SCENE_ID::GAMEMAIN);
		break;
	default:
		break;
	}
}
