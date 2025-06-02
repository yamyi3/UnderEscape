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
	//�n�ʂ̍��W
	vivid::Vector2 round_pos;

	//�Օ����̍��W
	vivid::Vector2 wall_pos;
	//�Օ����̕�
	float wall_width;
	//�Օ����̍���
	float wall_height;
	//�Օ����̐F
	unsigned int wall_color;
};