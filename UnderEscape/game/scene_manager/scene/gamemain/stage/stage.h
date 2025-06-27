#pragma once
#include "vivid.h"
#include "wallmanager/wallmanager.h"
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

	bool CheckHitPlayer(const vivid::Vector2& center_pos, int height, int width) { WallManager::GetInstance().CheckHitPlayer(center_pos, height, width); }
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
	//�n�ʂ̍����̎擾
	float GetRoundHeight(void)
	{
		return round_pos->y;
	}

	void GenerateObject(int x, int y, int Object_ID);

	void GenerateEnemy(int x, int y, int Object_ID);

private:
	//�n�ʂ̍��W
	vivid::Vector2 round_pos[3];

	//�X�e�[�W�̎n�_�̍��W
	static vivid::Vector2	start_pos;

	//�X�e�[�W�̏I�_�̍��W
	static vivid::Vector2	goal_pos;

	//�Օ����̍��W
	vivid::Vector2 wall_pos;
	//�Օ����̕�
	static const float wall_width;
	//�Օ����̍���
	static const float wall_height;
	//�Օ����̐F
	static unsigned int wall_color;

	//�n��1���̕�
	static const float	round_width;
	//�n�ʂ̉摜�̖���
	int		max_round;
	//�X�N���[���̑��x
	float	sc_speed;
	//���@�̒ʏ푬�x
	static const float	walk_speed;
	//���@�̃_�b�V�����x
	static const float	dash_speed;
	//���@�̕��s���x
	static const float	sneak_speed;

	//�V���O���g���p�^�[���̐ݒ�
	Stage(void) = default;
	~Stage(void) = default;
	Stage(const Stage& rhs) = default;
	Stage& operator = (const Stage& rhs) = default;






	static const int g_map_chip_size;
	static const int g_map_chip_count_width=40;
	static const int g_map_chip_count_height=11;
	// �}�b�v�`�b�v�ԍ���񋓌^�Œ�` 
	enum class MAP_CHIP_ID
	{
		EMPTY,
		GROUND,
		BLOCK,
		WALL,
		ENEMY_AREA,
		R_ENEMY,
		L_ENEMY,
		START,
		GOAL,
	};

	// �z�u�f�[�^�����Ă������߂̓񎟌��z��(����) 
	MAP_CHIP_ID g_Map[g_map_chip_count_height][g_map_chip_count_width] = { MAP_CHIP_ID::EMPTY };
	bool g_map_flg[g_map_chip_count_height][g_map_chip_count_width] = { true };
};