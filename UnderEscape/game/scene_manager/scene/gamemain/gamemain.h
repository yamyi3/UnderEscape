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

	void Pause();			//ポーズに以降する処理
	void PauseMenu(void);	//ポーズメニューの動作
	void DrawPause(void);	//ポーズメニューの描画

private:

	//自機移動と壁移動の切り替え座標
	vivid::Vector2	change_pos;
	//ポーズメニューの切り替え[true]の場合はポーズメニューが起動、[false]の場合はポーズメニューは開いていない
	bool pause_menu;

	vivid::Vector2	frame_pos;		//ポーズメニューのフレームの座標
	vivid::Vector2	menu_pos[3];		//各メニューの座標
	const int		font_size;		//メニューのフォントサイズ
	std::string		menu_list[3]	//各メニューの表示内容
	{
		"ゲーム設定",
		"タイトルへ戻る",
		"閉じる"
	};
	unsigned int	color_list[3]	//メニューの色リスト
	{
		0xff000000,		//デフォルトカラー
		0xffffff00,		//選択中の色
		0xffff0000		//決定時の色
	};
	unsigned int	menu_color[3];	//各メニューの色
	int				menu_cursor;	//現在選択しているメニューの記憶用
};