#pragma once
#include "vivid.h"
#include"../scene.h"


class GameMainScene : public IScene
{
public:
	GameMainScene(void);
	~GameMainScene(void) = default;

	void Initialize(void)override;
	void Update(void)override;
	void Draw(void)override;
	void Finalize(void)override;

	bool GameFlg() { return true; }
	void Pause();	//ポーズに以降する処理
private:

	//自機移動と壁移動の切り替え座標
	vivid::Vector2	change_pos;
	//ポーズメニューの切り替え[true]の場合は止まる[false]の場合は動く
	bool pause_menu;
};