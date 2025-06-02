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

void GameClear::Draw()
{
	cursor_move();
	vivid::DrawTexture("data\\�X�e�[�W�N���A.webp", pos3, color);
	vivid::DrawTexture("data\\���̃X�e�[�W��.webp", pos1, color);
	vivid::DrawTexture("data\\�^�C�g���ɂ��ǂ�.webp", pos2, color);
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
