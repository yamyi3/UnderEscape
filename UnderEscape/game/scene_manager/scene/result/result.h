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

	void cursor_move();		//カーソルの移動
	bool GetCursor();		//カーソルの取得
private:
	enum class RESULT		//リザルトの分岐
	{
		GameClear,
		GameOver
	};
	RESULT result = RESULT::GameClear;
protected:
	unsigned int defult_color;				//色
	bool left_right;						//カーソルの右左位置[右の場合はtrue][左の場合はfalse]
	vivid::Vector2 cursor_pos;			//カーソルの表示位置
	vivid::Vector2 left_pos;			//左の選択肢の位置
	vivid::Vector2 right_pos;			//右の選択肢の位置
	vivid::Vector2 result_pos;			//ゲームオーバーorゲームクリアの位置
};