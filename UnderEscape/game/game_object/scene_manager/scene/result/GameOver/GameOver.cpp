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

void  GameOver::Draw()
{
	//vivid::DrawTexture("data\\�Q�[���I�[�o�[.jpg", result_pos, defult_color);		//���S
	//vivid::DrawTexture("data\\���Ȃ���1.webp", left_pos, defult_color);			//���̑I��
	//vivid::DrawTexture("data\\�^�C�g���ɂ��ǂ�.webp", right_pos, defult_color);		//�E�̑I��
//#ifdef _DEBUG
	DrawCursor();
	vivid::DrawText(40, "GameOverScene", vivid::Vector2(0.0f, 0.0f), 0xffffffff);
	vivid::DrawText(40, "GAMEOVER", (result_pos - vivid::Vector2(-300, 200)), defult_color);
	vivid::DrawText(40, "���Ȃ���", menu_pos[0],  defult_color);
	vivid::DrawText(40, "�^�C�g����", (menu_pos[1]),  defult_color);
//#endif
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
