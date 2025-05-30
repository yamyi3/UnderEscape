#pragma once
#include "vivid.h"

class Enemy
{
public:
	Enemy(void);
	~Enemy(void) = default;

	void Initialize(void);
	void Update(void);
	void Draw(void);
	void Finalize(void);

	vivid::Vector2 GetEnemyPos(void);

	float GetCircleRadius(void);

	vivid::Vector2	GetCircleCenterPos(void);

private:
	vivid::Vector2	ePos;
	const float		eHeight;
	const float		eWidth;
	const float		eCircleRadius;
	vivid::Vector2	eCircleCenterPos;
};