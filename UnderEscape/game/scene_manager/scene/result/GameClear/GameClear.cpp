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
//�`��
void GameClear::Draw()
{
	cursor_move();
	vivid::DrawTexture("data\\�X�e�[�W�N���A.webp",result_pos, defult_color);	//���S
	vivid::DrawTexture("data\\���̃X�e�[�W��.webp", left_pos, defult_color);	//���̑I��
	vivid::DrawTexture("data\\�^�C�g���ɂ��ǂ�.webp",right_pos, defult_color);	//�E�̑I��
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
