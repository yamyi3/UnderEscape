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
//�`��
void  GameOver::Draw()
{
	
	vivid::DrawTexture("data\\�����֌W\\�Q�[���I�[�o�[�w�i.png", vivid::Vector2(0.0f, 0.0f), 0xffffffff);
	vivid::DrawTexture("data\\�����֌W\\GAMEOVER.png", result_pos, 0xffffffff);
	vivid::DrawTexture("data\\�����֌W\\�I�[�o�[���g���C.png", menu_pos[0], 0xffffffff);
	vivid::DrawTexture("data\\�����֌W\\�I�[�o�[�^�C�g���֖߂�.png", menu_pos[1], 0xffffffff);
	vivid::DrawTexture("data\\�����֌W\\�Q�[���I�[�o�[�J�[�\��.png", cursor_pos, 0xffffffff);
}

void  GameOver::Finalize()
{
}

void GameOver::Scene()
{
	switch (picture)
	{
	case GameOverScene::Title:		//�^�C�g��
		SceneManager::GetInstance().ChangeScene(SCENE_ID::TITLE);
		break;
	case GameOverScene::Retry:		//���g���C
		SceneManager::GetInstance().ChangeScene(SCENE_ID::GAMEMAIN);
		break;
	default:
		break;
	}
}
