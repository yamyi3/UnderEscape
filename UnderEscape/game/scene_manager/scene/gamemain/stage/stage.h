#pragma once
#include "vivid.h"

class Stage
{
public:
	//�C���X�^���X�𐶐��A�擾
	static Stage& GetInstance(void);
	//������
	void Initialize(void);
	//�X�V
	void Update(void);
	//�`��
	void Draw(void);
	//���
	void Finalize(void);
	//�X�e�[�W�̃X�N���[������
	void ScrollStage(void);
	//�n�ʍ��W�̃X�^�[�g�n�_�擾
	vivid::Vector2 GetStartpos(void)
	{
		return vivid::Vector2(0.0f, 0.0f);
	}
	//�n�ʂ̃S�[���n�_�̍��W�擾
	vivid::Vector2 GetGoalpos(void)
	{
		return vivid::Vector2((Stage::max_round * Stage::round_width), 0.0f);
	}
	//��Q�����W�̎擾
	vivid::Vector2 GetWallpos(void)
	{
		return wall_pos;
	}
	//��Q���̕��̎擾
	float GetWallWidth(void)
	{
		return wall_width;
	}
	//��Q���̍����̎擾
	float GetWallHeight(void)
	{
		return wall_height;
	}

private:
	//�n�ʂ̍��W
	vivid::Vector2 round_pos[3];

	//�Օ����̍��W
	vivid::Vector2 wall_pos;
	//�Օ����̕�
	static const float wall_width;
	//�Օ����̍���
	static const float wall_height;
	//�Օ����̐F
	static unsigned int wall_color;

	//�n��1���̕�
	float	round_width;
	//�n�ʂ̉摜�̖���
	int		max_round;
	//�X�N���[���̑��x
	float	sc_speed;
	//���@�̒ʏ푬�x
	static const float	run_speed;
	//���@�̃_�b�V�����x
	static const float	dash_speed;
	//���@�̕��s���x
	static const float	walk_speed;

	//�V���O���g���p�^�[���̐ݒ�
	Stage(void) = default;
	~Stage(void) = default;
	Stage(const Stage& rhs) = default;
	Stage& operator = (const Stage& rhs) = default;

};