//character.h
#pragma once
#include "vivid.h"

enum class CHARA_STATE
{
	WAIT,
	WALK,
	RUN,
	SNEAKWAIT,
	SNEAKWALK,
	JUMP,

	MAX,
};

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
	void RoundHit(float);
	//��Q��(��)�Ɋ��S�ɉB��Ă��鎞�̏���
	bool CheckWallHit(vivid::Vector2, float, float);
	//�G�̎��E�ɓ����Ă��Ȃ����̔��f
	bool CheckEnemyHit(vivid::Vector2, float);
	//�A�C�e���̎擾���f
	bool CheckObtainItem(vivid::Vector2, vivid::Vector2, float, float);
	//�ǂ⎋�E�ɓ����������̐F�̕ύX
	void CheckHit(vivid::Vector2, float, float, vivid::Vector2, float);
	void CheckHit(vivid::Vector2, float, float,bool);
	//����������
	bool CheckThrow(void);
	//�u��������
	bool checkPut(void);
	//�Q�[�W�̏㏸����
	void UpperGauge(void);
	//�Q�[�W�̉��~����
	void DownerGauge(void);
	//�A�j���[�V�����̍X�V
	void UpdateAnimation(void);
	//���@�̈ړ����x���Ƃ̏�Ԃ̔���
	void CheckMoveState(void);
	//�_�b�V�����̃X�^�~�i�̏���
	void DashStamina(void);
	//�X�^�~�i�̉񕜏���
	void RecoveryStamina(void);

	//���W�̎擾
	vivid::Vector2 GetCharapos(void) { return cPos; }
	//���@�̕��̎擾
	float GetCharaWidth(void) { return ch_width; }
	//���@�̍����̎擾
	float GetCharaHeight(void) { return ch_height; }
	//���@�̃A�C�e���擾�t���O�̎擾
	bool GetCatchFlg(void) { return cCatch; }
	//���s���x�̎擾
	float GetSneak(void) { return sneak_speed; }
	//�ʏ푬�x�̎擾
	float GetWalk(void) { return walk_speed; }
	//�_�b�V�����x�̎擾
	float GetDash(void) { return dash_speed; }
	//�Օ��t���O�̎擾
	bool GetShilding(void) { return cShielding; }	//�V�[���h��Ԃ̎擾
private:
	vivid::Vector2 cPos;				//���@�̍��W
	vivid::Vector2 m_Velocity;			//�������܂ޑ��x�v�Z

	//->�`��֌W
	int	c_anime_frame;								//�A�j���[�V�����̍X�V
	int	c_anime_timer;								//�A�j���[�V�����^�C�}�[
	int	c_change_anime_timer;						//�A�j���[�V�����̐؂�ւ���l
	int	c_change_anime_frame;						//�e�A�j���[�V�����̖���
	std::string	c_image[(int)CHARA_STATE::MAX] =	//���@�̉摜
	{	"data\\���@\\�O�ҋ@�X�v���b�h.png",			//�ҋ@
		"data\\���@\\�O�����X�v���b�h.png",			//���s
		"data\\���@\\�O����X�v���b�h.png",			//�_�b�V��
		"data\\���@\\�O���Ⴊ�ݑҋ@�X�v���b�h.png",	//���Ⴊ�ݑҋ@
		"data\\���@\\�O���Ⴊ�ݕ����X�v���b�h.png",	//���Ⴊ�ݕ���
		"data\\���@\\�O�W�����v�X�v���b�h.png" };	//�W�����v
	vivid::Rect		c_rect;							//�摜�̕`��͈�
	vivid::Vector2	c_anchor;						//���@�̊g���_
	vivid::Vector2	c_scale;						//���@�̃X�P�[��
	float			c_rotate;						//���@�̉�]�p�x
	//<-�`��֌W

	static const float ch_width;		//���@�̕�
	static const float ch_height;		//���@�̍���
	static unsigned int color;			//���@�̐F

	static float ch_speed;				//���@�̈ړ����x(����p�̕ϐ�)
	static const float walk_speed;		//���@�̕��s���̈ړ����x
	static const float dash_speed;		//���@�̃_�b�V�����̈ړ����x
	static const float sneak_speed;		//���@�̂��Ⴊ�ݎ��̈ړ����x
	static const float fatigue_speed;	//���@�̔�J���̈ړ����x(�X�^�~�i��0�̎��̈ړ����x)
	const float jump_speed = -20.0f;	//���@�̃W�����v�̑��x
	const float fall_speed = 0.7f;		//���@�̗������x(�d��)
	const float m_friction = 0.8f;		//���������
	const float cut_speed = 0.1f;		//���@�̈ړ���0�ɂ���

	vivid::Rect gauge_rect;				//�Q�[�W�摜�̕\����
	vivid::Vector2 gPos;				//�Q�[�W�̕\�����W
	const int max_gauge = 10;			//���@�̔����Q�[�W�̍ő��
	static int gauge;					//���@�̌��݂̔����Q�[�W�̗�
	const int one_gauge_frame = 60;		//�����Q�[�W1��������̑����ɂ�����t���[����
	static int gauge_count_frame;		//�����Q�[�W�����܂��Ă���Ԃ̃t���[�����J�E���^
	const int downer_frame = 180;		//�����Q�[�W��1����܂łɂ�����t���[����
	static int down_gauge_count;		//�Q�[�W�����̃J�E���^

	static const int	c_max_stamina;		//���@�̃X�^�~�i�̍ő�l
	static int			c_stamina_gauge;	//���@�̃X�^�~�i�̃Q�[�W
	static float		c_stamina_count;	//�X�^�~�i�̌������x��}��J�E���^
	static float		c_stamina_recovery;	//�X�^�~�i�񕜊J�n�܂ł̃J�E���^
	static bool			c_stamina_dash;		//�_�b�V���\�����ʂ���t���O
	static bool			c_stamina_fatigue;	//���@����J��Ԃ����ʂ���t���O

	static bool m_LandingFlag;			//�ڒn�t���O
	static bool cCatch;					//�I�u�W�F�N�g���������Ă��邩���ʂ���t���O
	static bool cAlive;					//�����t���O
	bool cShielding;					//�Օ��ɓ����Ă��邩���肷��t���O
	CHARA_STATE chara_state;			//���@�̏��

	//�C���X�^���X�̐���
	Character(void) = default;
	~Character(void) = default;
	Character(const Character& rhs) = default;
	Character& operator = (const Character& rhs) = default;
};