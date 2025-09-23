//リザルトシーンクラス
#pragma once
#include"../scene.h"
#include"vivid.h"
class ResultScene :public IScene
{
public:
	ResultScene();
	~ResultScene() = default;
	void Initialize()override;
	void Update()override;
	void Draw()override;
	void Finalize()override;
	//更新
	void Update(bool);

	void CursorMove();		//カーソルの移動
	bool GetCursor();		//カーソルの取得
private:
	enum class RESULT		//リザルトの分岐
	{
		GameClear,
		GameOver
	};
	RESULT result = RESULT::GameClear;
protected:
	unsigned int defult_color;			//色
	bool left_right;					//カーソルの右左位置[右の場合はtrue][左の場合はfalse]
	vivid::Vector2 cursor_pos;			//カーソルの表示位置
	vivid::Vector2 menu_pos[2];			//メニューの表示位置(0が左、1が右)
	vivid::Vector2 result_pos;			//ゲームオーバーorゲームクリアの位置
};