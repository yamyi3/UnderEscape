#pragma once
#include "vivid.h"
#include "..\item_id.h"
#include "../item.h"


class SoundItem : public Item
{
public:
	SoundItem();
	~SoundItem();
	//������
	void Initialize(vivid::Vector2 position);
	//�`��
	void Draw(void);
	//�v���C���[�������Ă����Ԃ̏���
	void GetMove(vivid::Vector2, float, float);
	//�v���C���[����������̏���(�}�E�X�j
	void UseMove(float, vivid::Vector2);


private:
	float Xspeed ;						//�򋗗��̃}�C�i�X�{��(X��)�l������������Ɣ򋗗����L�т�
	float Yspeed	;					//�򋗗��̃}�C�i�X�{��(Y��)�l������������Ɣ򋗗����L�т�
	vivid::Vector2 Mouse;				//���L��������̃}�E�X�̍��W
	
	static const float item_height;		//�A�C�e���I�u�W�F�N�g�̍���
	static const float item_width;		//�A�C�e���I�u�W�F�N�g�̕�
	static const float item_radius;		//�A�C�e���I�u�W�F�N�g�̕�

};

