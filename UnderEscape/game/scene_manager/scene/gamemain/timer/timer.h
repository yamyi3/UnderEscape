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
	int max_timer;					//1�X�e�[�W�̍ő�b��
	const int one_second_flame;		//1�b������̃t���[����
	
	int flame_timer;				//�t���[���J�E���g�ł̃X�e�[�W���̕b��

	int hundred_cnt;				//�\���b���̕S�̈�
	int ten_cnt;					//�\���b���̏\�̈�
	int one_cnt;					//�\���b���̈�̈�
};