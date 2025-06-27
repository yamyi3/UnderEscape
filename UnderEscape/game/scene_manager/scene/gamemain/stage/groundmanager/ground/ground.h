#pragma once
#include "vivid.h"
class Ground
{
public:
	Ground();
	~Ground() = default;
	//初期化
	void Initialize(vivid::Vector2 pos, float V, float H);
	void Initialize(vivid::Vector2 pos1, vivid::Vector2 pos2);
	void Initialize(vivid::Vector2 pos, float V, float H, int color);
	void Initialize(vivid::Vector2 pos1, vivid::Vector2 pos2, int color);
	//更新
	void Update(void);
	//描画
	void Draw(float scroll);
	// 開放
	void Finalize();
	//プレイヤーとの当たり判定をチェック
	bool CheckHitPlayer(const vivid::Vector2& center_c_pos, int ch_height, int ch_width);

	bool IsActive(void)const { return m_ActiveFlag; }
	void Destroy(void) { m_ActiveFlag = false; }

private:
	static const std::string ground_picture_name;
	static const int ground_picture_width_size;
	static const int ground_picture_height_size;


	vivid::Vector2 w_Pos;
	vivid::Vector2 w_Scale;
	float w_WidthSize;					//障害物の横のドット数
	float w_HeightSize;                 //障害物の縦のドット数
	unsigned int w_color;

	bool m_ActiveFlag;	//アクティブフラグ
};