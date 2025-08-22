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
	void Pause();	//ポーズに移行する処理

	void PauseMenu();	//ポーズメニュー内の動作、情報更新
	void DrawPause();	//ポーズメニューの描画
private:

	//自機移動と壁移動の切り替え座
	vivid::Vector2	change_pos;
	//ポーズメニューの切り替え[true]の場合は止まる[false]の場合は動く
	bool pause_menu;

	vivid::Vector2	frame_pos;		//メニューのフレームの座標
	vivid::Vector2	menu_pos[3];	//ポーズメニューの内容ごとの座標(設定、タイトルへ戻る、ポーズ閉じる)
	const int		font_size;		//文字の大きさ
	int				menu_cursor;	//ポーズメニューの現在選択している場所
	std::string		menu_list[3] =	//ポーズメニューの仮置き用文字
	{
		"ゲーム設定",
		"タイトルへ戻る",
		"閉じる"
	};
	unsigned int	menu_color[3];	//各メニューの色
	unsigned int	color_list[3] = //メニューの文字の色
	{
		0xff000000,		//デフォルト
		0xffffff00,		//決定
		0xffff0000		//選択状態の位置
	};

};