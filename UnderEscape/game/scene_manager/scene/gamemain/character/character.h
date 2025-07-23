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

enum class CHARA_SKILL
{
	ANIMALLEG,
	INVISIBLE,

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

	//�X�e�[�W�Ƃ̓����蔻�菈��
	void StageHit();
	void HStageHit();
	void VStageHit();
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
	//�A�j���[�V�����̍X�V
	void UpdateAnimation(void);
	//���@�̈ړ����x���Ƃ̏�Ԃ̔���
	void CheckMoveState(void);
	//�_�b�V�����̃X�^�~�i�̏���
	void DashStamina(void);
	//�X�^�~�i�̉񕜏���
	void RecoveryStamina(void);
	//�X�^�~�i��0�ɂȂ�����̏���
	void LimitStamina(void);
	//�X�L���̔�������
	void SkillMove(void);
	//�����\�X�L���̐؂�ւ�����
	void ChangeSkill(void);
	//�N�[���^�C���̏���
	void CoolTime(void);

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

	//�X�N���[���ϐ��X�V�p
	void Scroll_Update();
	//�X�N���[���̒l��Ԃ��ϐ�
	vivid::Vector2 GetScroll() { return Scroll; }

private:

	//�X�N���[���p�̕ϐ�
	vivid::Vector2 Scroll;
	static const float scroll_width_space;
	static const float scroll_height_space;

	vivid::Vector2 m_Velocity;			//�������܂ޑ��x�v�Z

	//->�`��֌W
	//->���@�֌W
	vivid::Vector2 cPos;							//���@�̍��W
	static const float ch_width;					//���@�̕�
	static const float ch_height;					//���@�̍���
	static unsigned int color;						//���@�̐F
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
	//<-���@�֌W
	//->�X�^�~�i�֌W
	vivid::Vector2	stamina_pos;					//�X�^�~�i�̕`����W
	std::string c_dash_image[2] =		
		//�X�^�~�i�̉摜
	{	"data\\���@\\���E�X�^�~�i.png",				//����Ȃ���Ԃ̃X�^�~�i
		"data\\���@\\�ʏ�X�^�~�i.png" };			//�ʏ펞�̃X�^�~�i

	static const int stamina_width;					//�X�^�~�i�Q�[�W�̕�(1������)
	static const int stamina_height;				//�X�^�~�i�Q�[�W�̍���
	vivid::Rect		stamina_rect;					//�摜�̕`��͈�
	vivid::Vector2	stamina_anchor;					//�X�^�~�i�̊g���_
	vivid::Vector2	stamina_scale;					//�X�^�~�i�̃X�P�[��
	//<-�X�^�~�i�֌W
	//<-�`��֌W

	//->���@�̑��x�֌W
	static float ch_speed;				//���@�̈ړ����x(����p�̕ϐ�)
	static const float walk_speed;		//���@�̕��s���̈ړ����x
	static const float dash_speed;		//���@�̃_�b�V�����̈ړ����x
	static const float sneak_speed;		//���@�̂��Ⴊ�ݎ��̈ړ����x
	static const float fatigue_speed;	//���@�̔�J���̈ړ����x(�X�^�~�i��0�̎��̈ړ����x)
	const float jump_speed = -20.0f;	//���@�̃W�����v�̑��x
	const float fall_speed = 0.7f;		//���@�̗������x(�d��)
	const float m_friction = 0.8f;		//���������
	const float cut_speed = 0.1f;		//���@�̈ړ���0�ɂ���
	vivid::Vector2 accelerator;
	//<-���@�̑��x�֌W
	// 
	//->�X�^�~�i�֌W
	static const int	c_max_stamina;		//���@�̃X�^�~�i�̍ő�l
	static int			c_stamina_gauge;	//���@�̃X�^�~�i�̃Q�[�W
	static int			c_stamina_count;	//�X�^�~�i�̌������x��}��J�E���^
	static int			c_limit_recovery;	//��J��Ԃ̃X�^�~�i�񕜊J�n�܂ł̃J�E���^
	static bool			c_stamina_dash;		//�_�b�V���\�����ʂ���t���O
	static bool			c_stamina_fatigue;	//���@����J��Ԃ����ʂ���t���O
	static int			c_stamina_recovery;	//�X�^�~�i�̉񕜃J�E���^
	//<-�X�^�~�i�֌W

	//->�X�L���֌W
	static const int	activation_time;	//�X�L���̔�����̌��ʎ���
	bool				skill_active_flag;	//�X�L���̃A�N�e�B�u�t���O
	int					active_count;		//�X�L���������̃J�E���^
	static const int	skill_cool_time;	//�X�L���̃N�[���^�C���̍ő吔
	int					cool_time_count;	//�N�[���^�C���̃J�E���^
	bool				skill_cool_flag;	//�N�[���^�C���������Ăяo���t���O
	/*�e�A�N�e�B�u�t���O�͎g�p�X�L���̑I���Ɏg��(�X�L���̓{�^���ł̐؂�ւ����ɂ���)*/
	//<-�X�L���֌W

	static bool m_LandingFlag;			//�ڒn�t���O
	static bool cCatch;					//�I�u�W�F�N�g���������Ă��邩���ʂ���t���O
	static bool cAlive;					//�����t���O
	bool cShielding;					//�Օ��ɓ����Ă��邩���肷��t���O
	CHARA_STATE chara_state;			//���@�̏��
	CHARA_SKILL chara_skill;			//�X�L���̎g�p���

	//->�C���X�^���X�̐���
	Character(void) = default;
	~Character(void) = default;
	Character(const Character& rhs) = default;
	Character& operator = (const Character& rhs) = default;
	//<-�C���X�^���X�̐���

};