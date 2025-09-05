#pragma once
#include "vivid.h"
#include "..\item_id.h"
#include "../item.h"


class FlashItem : public Item
{
public:
	FlashItem();
	~FlashItem();
	//������
	void Initialize(vivid::Vector2 position);
	//�`��
	void Draw(void);
	//�v���C���[�������Ă����Ԃ̏���
	void GetMove(vivid::Vector2, float, float);
	//�v���C���[����������̏���(�}�E�X�j
	void UseMove(vivid::Vector2);

	float GetEffectiveArea()
	{
		return m_Area;
	}

private:
	float Xspeed;						//�򋗗��̃}�C�i�X�{��(X��)�l������������Ɣ򋗗����L�т�
	float Yspeed;						//�򋗗��̃}�C�i�X�{��(Y��)�l������������Ɣ򋗗����L�т�
	vivid::Vector2 Mouse;				//���L��������̃}�E�X�̍��W
	bool Flash_State;					//�M���̏��

	static const float item_height;		//�A�C�e���I�u�W�F�N�g�̍���
	static const float item_width;		//�A�C�e���I�u�W�F�N�g�̕�
	static const float item_radius;		//�A�C�e���I�u�W�F�N�g�̕�	
	static const int	max_item_time;		//�A�C�e���̌��ʎ���	
	static const int	max_number_of_times;	//�A�C�e���̎g�p��
};

