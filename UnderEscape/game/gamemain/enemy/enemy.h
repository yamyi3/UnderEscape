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
	void Initialize(void);
	void Update(void);
	void Draw(void);
	void Finalize(void);

	vivid::Vector2 GetEnemyPos(void);

	float GetCircleRadius(void);

	vivid::Vector2	GetCircleCenterPos(void);

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
	const int e_width_size = 64;						//�G�l�~�[�̉��̃h�b�g��
	const int e_height_size = 64;                       //�G�l�~�[�̏c;;;;�̃h�b�g��
	vivid::Vector2 ePos = { 0.0f,0.0f };				//�G�l�~�[�̕`��Ɏg�p����|�W�V����
	vivid::Rect eRect = { 0,0,e_height_size,e_width_size };						//�G�l�~�[�̉摜�͈�
	vivid::Vector2 eAnchor = { e_width_size / 2.0f,e_height_size / 2.0f };		//�G�l�~�[�̃A���J�[
	vivid::Vector2 eScale = { 1.0f,1.0f };				//�G�l�~�[�̃X�P�[��

	const int exclamation_width_size = 32;						//!�̉��̃h�b�g��
	const int exclamation_height_size = 32;                       //!�̏c�̃h�b�g��
	vivid::Vector2 exclamationPos = { 0.0f,0.0f };				//!�̕`��Ɏg�p����|�W�V����
	vivid::Rect exclamationRect = { 0,0,exclamation_height_size,exclamation_width_size };						//!�̉摜�͈�
	vivid::Vector2 exclamationAnchor = { exclamation_width_size / 2.0f,exclamation_height_size / 2.0f };		//!�̃A���J�[
	vivid::Vector2 exclamationScale = { 1.0f,1.0f };				//!�̃X�P�[��

	float Rwool;										//�G�l�~�[���񒆂̉E���̍ő�s���͈͗p�ϐ�
	float Lwool;										//�G�l�~�[���񒆂̍����̍ő�s���͈͗p�ϐ�
	const float eSpeed = 4;								//�G�l�~�[�̏��񒆂̈ړ����x
	const float eChaseSpeed = 6;						//�G�l�~�[�̃v���C���[�ǐՒ��̈ړ����x
	const int Source_End_Range = 4;						//�x�����W�Ƃ̂����̍������̐��l���Z���Ȃ�����ǐՂ��I������B
	int gravity = 0;										//�W�����v�A�d�͗p�̕ϐ�
	bool jpflg;											//�W�����v�̉ۂ̔���p
	float eGround = 600;									//�n�ʂ̍���
	int eVector = 1;									//�G�l�~�[�̌����Ă�����p
	vivid::Vector2 ChasePos;							//�ǐՖڕW�n�_;
	int Vigilance_Timer = 0;							//�ǐՖڕW�n�_���B��̑ҋ@���ԗp
	const int Vigilance_time = 150;						//�ǐՖڕW�n�_���B��̑ҋ@�t���[����
	int Surprised_Timer = 0;							//�ǐՊJ�n�O�̒�~���ԗp
	const int Surprised_time = 30;						//�ǐՊJ�n�O�̒�~�t���[����
	const float enemy_jump_height = 150;				//�W�����v�̍���
	const float enemy_jump_upspeed = 3;					//�W�����v�̏㏸�X�s�[�h
	const float enemy_jump_downspeed = 100;				//�����X�s�[�h(�㏸�X�s�[�h�̉�����)

	const float		eCircleRadius;
	vivid::Vector2	eCircleCenterPos;

	eSTATUS eStatus = eSTATUS::Wandering;				//�G�l�~�[�̏�ԕۑ��p
};