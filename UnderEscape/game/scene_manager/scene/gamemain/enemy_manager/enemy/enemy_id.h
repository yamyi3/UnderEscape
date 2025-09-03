#pragma once
enum class ENEMY_ID
{
	SPIDER_ROBO,
	CREATURE,
};
enum class eSTATUS									//エネミーの状態の種類
{
	Stop,		//停止
	Wandering,	//徘徊
	Chase,		//追いかける
	Vigilance,	//警戒
	Surprised,	//驚く
	Kill,		//キル

	MAX,		//eSTATUSの最大値
};
enum class eCHASE_STATUS	//エネミーが追いかけている情報の判別用
{
	Hearing,	//聴覚
	Sight,		//視覚
};