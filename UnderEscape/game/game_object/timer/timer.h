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
	vivid::Vector2	m_TimerPosition;	//�^�C�}�[�̕\�����W
	int max_timer;					//1�X�e�[�W�̍ő�b��
	static const int one_second_flame;		//1�b������̃t���[����

	int flame_timer;				//�t���[���J�E���g�ł̃X�e�[�W���̕b��

	int hundred_cnt;				//�\���b���̕S�̈�
	int ten_cnt;					//�\���b���̏\�̈�
	int one_cnt;					//�\���b���̈�̈�
	int m_SecondTimer;				//�b���Z�̃J�E���^

	CTimer(void);
	~CTimer(void) = default;
	//�R�s�[�R���X�g���N�^
	CTimer(const CTimer& rhs);
	//������Z�q
	CTimer& operator = (const CTimer& rhs);
};