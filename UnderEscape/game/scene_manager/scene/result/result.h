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
	enum class RESULT
	{
		GameClear,
		GameOver
	};
	RESULT result = RESULT::GameClear;
protected:
	unsigned int color;				//色
	bool Right;						//カーソルの右左位置[右の場合はtrue][左の場合はfalse]
	vivid::Vector2 Cpos;			//カーソルの表示位置
	vivid::Vector2 pos1;			//左の選択肢の位置
	vivid::Vector2 pos2;			//右の選択肢の位置
	vivid::Vector2 pos3;			//ゲームオーバーorゲームクリアの位置
};