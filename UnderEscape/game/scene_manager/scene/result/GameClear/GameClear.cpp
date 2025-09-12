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
	
	//vivid::DrawTexture("data\\�X�e�[�W�N���A.webp",result_pos, defult_color);	//���S
	//vivid::DrawTexture("data\\���̃X�e�[�W��.webp", left_pos, defult_color);	//���̑I��
	//vivid::DrawTexture("data\\�^�C�g���ɂ��ǂ�.webp",right_pos, defult_color);	//�E�̑I��
#ifdef _DEBUG
	vivid::DrawText(40, "GameClearScene", vivid::Vector2(0.0f, 0.0f), 0xffffffff);
	vivid::DrawText(40, "���߂��ꂠ�[", result_pos, defult_color);
	vivid::DrawText(40, "���������I", result_pos, defult_color);
	vivid::DrawText(40, "�^�C�g�[��", result_pos, defult_color);
#endif
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
