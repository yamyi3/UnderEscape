#pragma once
#include"vivid.h"

class Teleport
{
public:
	Teleport();
	~Teleport()=default;
	//初期化
	void Initialize();
	void Initialize(vivid::Vector2);
	void Initialize(vivid::Vector2, vivid::Vector2);
	//更新
	void Update(void);
	//描画
	void Draw(void);
	//解放
	void Finalize(void);

	void InputTpPos(vivid::Vector2);

	bool GetTeleportFlg(vivid::Vector2 p_pos);
	vivid::Vector2 GetTeleportPos(vivid::Vector2 p_pos);

private:
	vivid::Vector2 TpPos[2];
	static const int TpCount;

	float ch_width;					//自機の幅
	float ch_height;				//自機の高さ
	int map_chip_size;
};