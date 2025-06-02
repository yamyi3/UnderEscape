//character.h
#pragma once
#include "vivid.h"

//���@�N���X
class Character
{
public:
	//�C���X�^���X�̎擾
	static Character& GetInstance(void);
	//������
	void Initialize(vivid::Vector2);
	//�X�V
	void Update(void);
	//�`��
	void Draw(void);
	//���
	void Finalize(void);

	//��ʒ[����o�Ȃ��悤�ɂ��鏈��
	void CheckWindow(void);
	//���@�̑��쏈��
	void Control(void);
	//�n�ʂ����蔲���Ȃ��悤�ɂ��鏈��
	void RoundHit(vivid::Vector2);
	//��Q��(��)�Ɋ��S�ɉB��Ă��鎞�̏���
	bool CheckWallHit(vivid::Vector2, float, float);
	//�G�̎��E�ɓ����Ă��Ȃ����̔��f
	bool CheckEnemyHit(vivid::Vector2, float);
	//�A�C�e���̎擾���f
	bool CheckObtainItem(vivid::Vector2, vivid::Vector2, float, float);
	//�ǂ⎋�E�ɓ����������̐F�̕ύX
	void CheckHit(vivid::Vector2, float, float, vivid::Vector2, float);
	//����������
	bool CheckThrow(void);
	//�u��������
	bool checkPut(void);
	//�Q�[�W�̏㏸����
	void UpperGauge(void);
	//�Q�[�W�̉��~����
	void DownerGauge(void);

	//���W�̎擾
	vivid::Vector2 GetCharapos(void)
	{
		return cPos;
	}
	float GetCharaWidth(void)
	{
		return ch_width;
	}
	float GetCharaHeight(void)
	{
		return ch_height;
	}
	bool GetCatchFlg(void)
	{
		return cCatch;
	}

private:
	vivid::Vector2 cPos;				//���@�̍��W
	vivid::Vector2 m_Velocity;			//�������܂ޑ��x�v�Z

	float ch_width = 125.0f;			//���@�̕�
	float ch_height = 192.0f;			//���@�̍���
	static unsigned int color;				//���@�̐F

	static float ch_speed;				//���@�̈ړ����x
	static const float run_speed;		//���@�̒ʏ�ړ����x
	static const float dash_speed;		//���@�̃_�b�V�����̈ړ����x
	static const float walk_speed;		//���@�̕��s���̈ړ����x
	const float jump_speed = -20.0f;	//���@�̃W�����v�̑��x
	const float fall_speed = 0.7f;		//���@�̗������x(�d��)
	const float m_friction = 0.8f;		//���������
	const float cut_speed = 0.1f;		//���@�̈ړ���0�ɂ���

	vivid::Rect gauge_rect;				//�Q�[�W�摜�̕\����
	vivid::Vector2 gPos;				//�Q�[�W�̕\�����W
	const int max_gauge = 10;			//���@�̔����Q�[�W�̍ő��
	static int gauge;							//���@�̌��݂̔����Q�[�W�̗�
	const int one_gauge_frame = 60;		//�����Q�[�W1��������̑����ɂ�����t���[����
	static int gauge_count_frame;				//�����Q�[�W�����܂��Ă���Ԃ̃t���[�����J�E���^
	const int downer_frame = 180;		//�����Q�[�W��1����܂łɂ�����t���[����
	static int down_gauge_count;				//�Q�[�W�����̃J�E���^

	static bool m_LandingFlag;			//�ڒn�t���O
	static bool cCatch;					//�I�u�W�F�N�g���������Ă��邩���ʂ���t���O
	static bool cAlive;					//�����t���O

	//�C���X�^���X�̐���
	Character(void) = default;
	~Character(void) = default;
	Character(const Character& rhs) = default;
	Character& operator = (const Character& rhs) = default;
};