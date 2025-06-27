#pragma once
#include "vivid.h"
#include "enemy_status_id.h"

class Enemy
{
public:
	Enemy(void);
	~Enemy(void) = default;

	void Initialize(vivid::Vector2 pos, float L, float R, float vector, float ground);//������
	void Initialize(vivid::Vector2 pos, float L, float R, float vector);//������
	void Initialize(vivid::Vector2 pos, float L, float R);//������
	void Initialize(vivid::Vector2 pos);//������
	void Initialize(void);
	void Update(void);
	void Draw(void);
	void Finalize(void);

	vivid::Vector2 GetEnemyPos(void);

	float GetCircleRadius(void);

	vivid::Vector2	GetCircleCenterPos(void);

	bool CheckHitPlayer(const vivid::Vector2& center_c_pos, int c_height, int c_width);

	bool IsActive(void)const { return m_ActiveFlag; }
	void Destroy(void) { m_ActiveFlag = false; }

	void input_player_pos(vivid::Vector2 p_pos) { ChasePos = p_pos; }
	void sound_sensor(vivid::Vector2 sound_source, float sound_size);	//���̔���
	bool e_wool_jump();					//�ǂɓ���������W�����v���锻��

	void jump();				//�W�����v
	vivid::Vector2 Gravity		//�d��
	(vivid::Vector2 pos			//�L�����N�^�[�|�W�V����
		, float yuka			//�n�ʂ̍���
		, int CharacterVSize	//�L�����̏c�����̃T�C�Y
		, vivid::Vector2 anchor	//�L�����̎�(�ݒ肵�Ă��Ȃ�������{ 0.0f,0.0f }�����)
		, float height			//�W�����v�̍���(�h�b�g�P��)
		, float upspeed			//�o��X�s�[�h
		, float downspeed		//����X�s�[�h(�o��X�s�[�h�̉������Ȃ̂�100����)
	);

private:
	static const int e_visibility_width_size;
	static const int e_visibility_height_size;

	static const int e_width_size;					//�G�l�~�[�̉��̃h�b�g��
	static const int e_height_size;                 //�G�l�~�[�̏c;;;;�̃h�b�g��

	static const int mark_width_size;		//!�̉��̃h�b�g��
	static const int mark_height_size;		//!�̏c�̃h�b�g��

	static const float eSpeed;						//�G�l�~�[�̏��񒆂̈ړ����x
	static const float eChaseSpeed;					//�G�l�~�[�̃v���C���[�ǐՒ��̈ړ����x
	static const int Source_End_Range;				//�x�����W�Ƃ̂����̍������̐��l���Z���Ȃ�����ǐՂ��I������B
	static const int Vigilance_time;				//�ǐՖڕW�n�_���B��̑ҋ@�t���[����

	static const int Surprised_time;				//�ǐՊJ�n�O�̒�~�t���[����
	static const float enemy_jump_height;			//�W�����v�̍���
	static const float enemy_jump_upspeed;			//�W�����v�̏㏸�X�s�[�h
	static const float enemy_jump_downspeed;		//�����X�s�[�h(�㏸�X�s�[�h�̉�����)

	static const float		eCircleRadius;

	vivid::Vector2 ePos;				//�G�l�~�[�̕`��Ɏg�p����|�W�V����
	vivid::Rect eRect;						//�G�l�~�[�̉摜�͈�
	vivid::Vector2 eAnchor;		//�G�l�~�[�̃A���J�[
	vivid::Vector2 eScale;				//�G�l�~�[�̃X�P�[��


	vivid::Vector2 markPos;				//!�̕`��Ɏg�p����|�W�V����
	vivid::Rect markRect;				//!�̉摜�͈�
	vivid::Vector2 markAnchor;		//!�̃A���J�[
	vivid::Vector2 markScale;				//!�̃X�P�[��

	float Rwool;										//�G�l�~�[���񒆂̉E���̍ő�s���͈͗p�ϐ�
	float Lwool;										//�G�l�~�[���񒆂̍����̍ő�s���͈͗p�ϐ�

	int gravity;									//�W�����v�A�d�͗p�̕ϐ�
	bool jpflg;											//�W�����v�̉ۂ̔���p
	float eGround;								//�n�ʂ̍���
	int eVector;									//�G�l�~�[�̌����Ă�����p
	vivid::Vector2 ChasePos;							//�ǐՖڕW�n�_;
	int Vigilance_Timer;							//�ǐՖڕW�n�_���B��̑ҋ@���ԗp
	int Surprised_Timer;							//�ǐՊJ�n�O�̒�~���ԗp


	bool m_ActiveFlag;	//�A�N�e�B�u�t���O

	vivid::Vector2	eCircleCenterPos;

	eSTATUS eStatus;				//�G�l�~�[�̏�ԕۑ��p
};