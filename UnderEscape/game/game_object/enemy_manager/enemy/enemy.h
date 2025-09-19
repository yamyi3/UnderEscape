#pragma once
#include "vivid.h"
#include "enemy_id.h"
#include "../../item_manager/item/item_id.h"
class Enemy
{
public:
	Enemy::Enemy(int w_size, int h_size, float speed, float chase_speed,float jump_height, float jump_upspeed, float jump_downspeed, float circle_radius ,bool viewing_angle,int stun);
	~Enemy(void) = default;

	virtual void Initialize(vivid::Vector2 pos, float L, float R, float vector, float ground);//������
	virtual void Initialize(vivid::Vector2 pos, float L, float R, float vector);//������
	virtual void Initialize(vivid::Vector2 pos, float L, float R);//������
	virtual void Initialize(vivid::Vector2 pos);//������
	virtual void Initialize(void);
	virtual void Update();
	virtual void Draw(vivid::Vector2 scroll);
	virtual void Finalize(void);

	vivid::Vector2 GetEnemyPos(void);

	float GetCircleRadius(void);

	vivid::Vector2	GetCircleCenterPos(void);

	bool CheckHitPlayer(const vivid::Vector2& center_c_pos, int c_height, int c_width ,bool shielding);
	bool CheckSearchPlayer(const vivid::Vector2& center_c_pos, int c_height, int c_width, bool shielding);

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
	void player_check(bool shielding);	//�G�̍��G�͈͓��Ɏ��L����������ƒǂ���������

	void ItemCheck(ITEM_ID id, vivid::Vector2 pos, bool active, float effect_area);
protected:

	int e_width_size;					//�G�l�~�[�̉��̃h�b�g��
	int e_height_size;                 //�G�l�~�[�̏c�̃h�b�g��

	static const int mark_width_size;		//!�̉��̃h�b�g��
	static const int mark_height_size;		//!�̏c�̃h�b�g��

	float eSpeed;						//�G�l�~�[�̏��񒆂̈ړ����x
	float eChaseSpeed;					//�G�l�~�[�̃v���C���[�ǐՒ��̈ړ����x
	static const int Source_End_Range;				//�x�����W�Ƃ̂����̍������̐��l���Z���Ȃ�����ǐՂ��I������B
	static const int Vigilance_time;				//�ǐՖڕW�n�_���B��̑ҋ@�t���[����

	static const int Surprised_time;				//�ǐՊJ�n�O�̒�~�t���[����
	float enemy_jump_height;			//�W�����v�̍���
	float enemy_jump_upspeed;			//�W�����v�̏㏸�X�s�[�h
	float enemy_jump_downspeed;		//�����X�s�[�h(�㏸�X�s�[�h�̉�����)

	float		eCircleRadius;			//���E�͈�

	vivid::Vector2 ePos;				//�G�l�~�[�̕`��Ɏg�p����|�W�V����
	vivid::Rect eRect;						//�G�l�~�[�̉摜�͈�
	vivid::Vector2 eAnchor;		//�G�l�~�[�̃A���J�[
	vivid::Vector2 eScale;				//�G�l�~�[�̃X�P�[��


	vivid::Vector2 markPos;				//!�̕`��Ɏg�p����|�W�V����
	vivid::Rect markRect;				//!�̉摜�͈�
	vivid::Vector2 markAnchor;		//!�̃A���J�[
	vivid::Vector2 markScale;				//!�̃X�P�[��

	float Rwall;										//�G�l�~�[���񒆂̉E���̍ő�s���͈͗p�ϐ�
	float Lwall;										//�G�l�~�[���񒆂̍����̍ő�s���͈͗p�ϐ�

	int gravity;									//�W�����v�A�d�͗p�̕ϐ�
	bool jpflg;											//�W�����v�̉ۂ̔���p
	float eGround;								//�n�ʂ̍���
	int eVector;									//�G�l�~�[�̌����Ă�����p
	vivid::Vector2 ChasePos;							//�ǐՖڕW�n�_;
	int Sight_Check_Timer;
	int Vigilance_Timer;							//�ǐՖڕW�n�_���B��̑ҋ@���ԗp
	int Surprised_Timer;							//�ǐՊJ�n�O�̒�~���ԗp

	int TurnAroundtimer;
	static const int turn_around_ct;

	bool WallTouchFlg;		//�ǂɐG�ꂽ���̔���ۑ�
	float WallTouchPosX;	//�ǂɐG�ꂽ���̈ʒu

	bool m_ActiveFlag;	//�A�N�e�B�u�t���O

	int stun_time;
	int StunTimer;	//�X�^�����ԗp

	/*
	�G�l�~�[�̎���p�p
	true	::�O���̂�
	false	::�S����
	*/
	bool ViewingAngle;

	std::string enemy_sight = "data\\�G���E.png";

	int AnimationTimer;
	static const int animation_change_time;
	int AnimationFrame;
	int AnimationMaxFrame[(int)eSTATUS::MAX];

	bool item_area;				//�A�C�e���̌��ʔ͈͓��ɂ��邩�ǂ����̃t���O
	vivid::Vector2 item_pos;		//�A�C�e���̍��W

	vivid::Vector2	eCircleCenterPos;

	eSTATUS eStatus;				//�G�l�~�[�̏�ԕۑ��p
	eCHASE_STATUS eChaseStatus;		//�G�l�~�[�̒ǐՏ��̔��ʗp
};