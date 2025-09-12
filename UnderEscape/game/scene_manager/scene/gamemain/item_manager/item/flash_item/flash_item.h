#pragma once
#include "vivid.h"
#include "..\item_id.h"
#include "../item.h"


class CFlashItem : public CItem
{
public:
	CFlashItem(void);
	~CFlashItem(void);
	//������
	void Initialize(vivid::Vector2 position);
	//�`��
	void Draw(void);
	//�v���C���[�������Ă����Ԃ̏���
	void GetMove(vivid::Vector2, float, float);
	//�v���C���[����������̏���(�}�E�X�j
	void UseMove();

	void SetOrbitPosition(vivid::Vector2 position, vivid::Vector2 c_pos);

private:
	float m_X_Speed;						//�򋗗��̃}�C�i�X�{��(X��)�l������������Ɣ򋗗����L�т�
	float m_Y_Speed;						//�򋗗��̃}�C�i�X�{��(Y��)�l������������Ɣ򋗗����L�т�
	vivid::Vector2 m_Mouse_Pos;				//���L��������̃}�E�X�̍��W

	static const float m_height;			//�A�C�e���I�u�W�F�N�g�̍���
	static const float m_width;				//�A�C�e���I�u�W�F�N�g�̕�
	static const float m_radius;			//�A�C�e���I�u�W�F�N�g�̕�	
	static const int	m_max_time;			//�A�C�e���̌��ʎ���	
	static const int	m_number_of_times;	//�A�C�e���̌��ʎ���	
	static const float m_effect_area;		//�A�C�e�����ʔ͈�
};

