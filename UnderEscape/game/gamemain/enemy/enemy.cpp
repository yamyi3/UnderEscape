#include "enemy.h"

Enemy::Enemy(void)
	: ePos(300.0f, 500.0f)
	, eWidth(400.0f)
	, eHeight(400.0f)
	, eCircleRadius(200.0f)
{
}

void Enemy::Initialize(void)
{
	eCircleCenterPos.x = ePos.x + eCircleRadius;
	eCircleCenterPos.y = ePos.y + eCircleRadius;
}

void Enemy::Update(void)
{
}

void Enemy::Draw(void)
{
	vivid::DrawTexture("data\\“GŽ‹ŠE.png", ePos);
}

void Enemy::Finalize(void)
{
}

vivid::Vector2 Enemy::GetEnemyPos(void)
{
	return ePos;
}

float Enemy::GetCircleRadius(void)
{
	return eCircleRadius;
}

vivid::Vector2 Enemy::GetCircleCenterPos(void)
{
	return eCircleCenterPos;
}
