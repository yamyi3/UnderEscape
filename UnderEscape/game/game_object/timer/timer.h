#pragma once
#include "vivid.h"

class CTimer
{
public:

	static CTimer& GetInstance(void);

	void Initialize(void);
	void Update(void);
	void Draw(void);
	void Finalize(void);

	void ChangeTimer(void);

	int GetTimer(void);

private:
	vivid::Vector2	m_TimerPosition;	//タイマーの表示座標
	int max_timer;					//1ステージの最大秒数
	static const int one_second_flame;		//1秒あたりのフレーム数

	int flame_timer;				//フレームカウントでのステージ内の秒数

	int hundred_cnt;				//表示秒数の百の位
	int ten_cnt;					//表示秒数の十の位
	int one_cnt;					//表示秒数の一の位
	int m_SecondTimer;				//秒換算のカウンタ

	CTimer(void);
	~CTimer(void) = default;
	//コピーコンストラクタ
	CTimer(const CTimer& rhs);
	//代入演算子
	CTimer& operator = (const CTimer& rhs);
};