#pragma once
#include"vivid.h"
#include"../../scene.h"
#include"../result.h"
class GameOver :public IScene, public ResultScene
{
public:
	GameOver();
	~GameOver() = default;
	void Initialize();
	void Update();
	void Draw();
	void Finalize();
	void Scene();		//�V�[���̐؂�ւ�
private:
	enum class GameOverScene
	{
		Retry,
		Title
	};
	GameOverScene picture = GameOverScene::Retry;
};
