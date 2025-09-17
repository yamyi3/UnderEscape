#pragma once
#include"vivid.h"
#include"../../scene.h"
#include"../result.h"
class GameClear :public IScene, public ResultScene
{
public:
	GameClear();
	~GameClear() = default;

	void Initialize();
	void Update();
	void Draw();
	void Finalize();
	void Scene();		//�V�[���̐؂�ւ�

private:
	enum class GameClearScene
	{
		Next_Stage								//���X�e�[�W�ɂ��������i�Q�[�����C���ɂ����j
		, Title									//�^�C�g���ɖ߂鏈��
	};
	GameClearScene picture = GameClearScene::Next_Stage;
};
