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
	void Scene();		//シーンの切り替え

private:
	enum class GameClearScene
	{
		Next_Stage								//次ステージにいく処理（ゲームメインにいく）
		, Title									//タイトルに戻る処理
	};
	GameClearScene picture = GameClearScene::Next_Stage;
};
