#pragma once
#include "vivid.h"

class Stage
{
public:
	Stage(void);
	~Stage(void) = default;

	void Initialize(void);
	void Update(void);
	void Draw(void);
	void Finalize(void);

	void ScrollStage(void);

	vivid::Vector2 GetRoundpos(void)
	{
		return round_pos;
	}
	vivid::Vector2 GetWallpos(void)
	{
		return wall_pos;
	}
	float GetWallWidth(void)
	{
		return wall_width;
	}
	float GetWallHeight(void)
	{
		return wall_height;
	}

private:
	//地面の座標
	vivid::Vector2 round_pos;

	//遮蔽物の座標
	vivid::Vector2 wall_pos;
	//遮蔽物の幅
	float wall_width;
	//遮蔽物の高さ
	float wall_height;
	//遮蔽物の色
	unsigned int wall_color;
};