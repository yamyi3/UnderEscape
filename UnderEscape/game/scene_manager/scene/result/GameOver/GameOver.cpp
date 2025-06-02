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
	if (GetCursor() == true && vivid::keyboard::Trigger(vivid::keyboard::KEY_ID::RETURN))
	{

		picture = GameOverScene::Title;
		GameOver::Scene();
	}
	if (GetCursor() == false && vivid::keyboard::Trigger(vivid::keyboard::KEY_ID::RETURN))
	{
		picture = GameOverScene::Retry;
		GameOver::Scene();
	}
}

void  GameOver::Draw()
{
	cursor_move();
	vivid::DrawTexture("data\\�Q�[���I�[�o�[.jpg", pos3, color);
	vivid::DrawTexture("data\\���Ȃ���1.webp", pos1, color);
	vivid::DrawTexture("data\\�^�C�g���ɂ��ǂ�.webp", pos2, color);

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
