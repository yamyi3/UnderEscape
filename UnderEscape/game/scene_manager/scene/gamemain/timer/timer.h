#pragma once

class Timer
{
public:
	Timer(void);
	~Timer(void) = default;

	void Initialize(void);
	void Update(void);
	void Draw(void);
	void Finalize(void);

	void ChangeTimer(void);

private:
	int max_timer;					//1ステージの最大秒数
	const int one_second_flame;		//1秒あたりのフレーム数
	
	int flame_timer;				//フレームカウントでのステージ内の秒数

	int hundred_cnt;				//表示秒数の百の位
	int ten_cnt;					//表示秒数の十の位
	int one_cnt;					//表示秒数の一の位
};