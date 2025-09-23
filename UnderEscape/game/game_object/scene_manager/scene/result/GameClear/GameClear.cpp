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
	vivid::DrawTexture("data\\�����֌W\\�Q�[���N���A�w�i.png", vivid::Vector2(0.0f, 0.0f), 0xffffffff);
	vivid::DrawTexture("data\\�����֌W\\GAMECLEAR.png", result_pos, 0xffffffff);
	vivid::DrawTexture("data\\�����֌W\\�N���A�ナ�g���C.png", menu_pos[0], 0xffffffff);
	vivid::DrawTexture("data\\�����֌W\\�N���A��^�C�g���֖߂�.png", menu_pos[1], 0xffffffff);
	vivid::DrawTexture("data\\�����֌W\\�J�[�\��.png", cursor_pos, 0xffffff00);
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
