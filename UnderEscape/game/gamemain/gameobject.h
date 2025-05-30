#pragma once
#include "vivid.h"
//�A�C�e���I�u�W�F�N�g�̏��
enum class ITEM_STATE
{
	DUMMY,		//�_�~�[
	PLACE,		//�ݒu
	GET,		//�v���C���[�擾
	THROW,		//�������Ă���
	BREAK,		//�j��
};

class Gameobject
{
public:
	Gameobject(void);
	~Gameobject(void) = default;

	//������
	void Initialize(vivid::Vector2);
	//�X�V
	void Update(vivid::Vector2, bool, float, float, bool, vivid::Vector2, bool);
	//�`��
	void Draw(void);
	//���
	void Finalize(void);
	//���鎞�̏���
	void BreakMove(void);
	//�v���C���[�������Ă����Ԃ̏���
	void GetMove(vivid::Vector2, float, float);
	//�v���C���[����������̏���
	void ThrowMove(vivid::Vector2);
	//�v���C���[���u������̏���
	void PutMove(vivid::Vector2);
	//�v���C���[����������̏���(�}�E�X�j
	void ThrowMove3(vivid::Vector2, vivid::Vector2);

	//�A�C�e���I�u�W�F�N�g�̍��W�擾
	vivid::Vector2 getItemPos(void)
	{
		return iPos;
	}
	//�A�C�e���I�u�W�F�N�g�̒��S�_�̎擾
	vivid::Vector2 GetItemCenter(void)
	{
		return iCenter;
	}
	//�A�C�e���I�u�W�F�N�g�̕��擾
	float GetItemWidth(void)
	{
		return item_width;
	}
	//�A�C�e���I�u�W�F�N�g�̍����擾
	float GetItemHeight(void)
	{
		return item_height;
	}

private:
	float Xspeed = 100.0f;				//�򋗗��̃}�C�i�X�{��(X��)�l������������Ɣ򋗗����L�т�
	float Yspeed = 20.0f;				//�򋗗��̃}�C�i�X�{��(Y��)�l������������Ɣ򋗗����L�т�
	vivid::Vector2 Mouse;				//���L��������̃}�E�X�̍��W
	vivid::Vector2 iPos;				//�A�C�e���I�u�W�F�N�g�̍��W
	vivid::Vector2 iCenter;				//�A�C�e���I�u�W�F�N�g�̒��S�_
	bool catchFlg;						//�擾�̔��f�t���O
	bool breakFlg;						//�A�C�e���I�u�W�F�N�g�̔j��̔��f�t���O
	bool itemFlg;						//���n�̔���
	const float item_height = 32.0f;	//�A�C�e���I�u�W�F�N�g�̍���
	const float item_width = 32.0f;		//�A�C�e���I�u�W�F�N�g�̕�
	const float throw_speed = 8.0f;		//�A�C�e���I�u�W�F�N�g�̓����鑬�x
	float item_fall;					//�A�C�e���I�u�W�F�N�g�̗������x
	unsigned int iColor;				//�A�C�e���I�u�W�F�N�g�̐F

	float Ga = 1.0;						//�d�͉����x
	float V = 0.0;						//�㏸���鏉��

	ITEM_STATE item_state = ITEM_STATE::PLACE;	//�A�C�e���I�u�W�F�N�g�̏��(������Ԃ�PLACE(�ݒu))
};