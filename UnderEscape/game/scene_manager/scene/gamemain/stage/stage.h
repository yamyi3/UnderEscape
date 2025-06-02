#pragma once
#include "vivid.h"

class Stage
{
public:
	static Stage& GetInstance(void);
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
	static const float wall_width;
	//遮蔽物の高さ
	static const float wall_height;
	//遮蔽物の色
	static unsigned int wall_color;

	Stage(void) = default;
	~Stage(void) = default;
	Stage(const Stage& rhs) = default;
	Stage& operator = (const Stage& rhs) = default;

};