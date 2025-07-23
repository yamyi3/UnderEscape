#pragma once
#include "vivid.h"

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
		return vivid::Vector2(200.0f, 500.0f);
	}
	//�n�ʂ̃S�[���n�_�̍��W�擾
	vivid::Vector2 GetGoalpos(void)
	{
		return goal_pos;
	}

	//�n�ʂ̍����̎擾

	float GetRoundHeight(vivid::Vector2 pos, float width, float height);
	float GetRWall(vivid::Vector2 pos, float width, float height);
	float GetLWall(vivid::Vector2 pos, float width, float height);
	float GetCeiling(vivid::Vector2 pos, float width, float height);

	bool CheckHitWallPlayer(const vivid::Vector2& pos, int height, int width);

	void GenerateObject(int x, int y, int Object_ID);

	void GenerateEnemy(int x, int y, int Object_ID);

	int GetStageWidthSize() { return g_map_chip_count_width * g_map_chip_size; }
	int GetStageHeightSize() { return g_map_chip_count_height * g_map_chip_size; }
private:


	//�X�e�[�W�̎n�_�̍��W
	static vivid::Vector2	start_pos;

	//�X�e�[�W�̏I�_�̍��W
	static vivid::Vector2	goal_pos;

	//�V���O���g���p�^�[���̐ݒ�
	Stage(void) = default;
	~Stage(void) = default;
	Stage(const Stage& rhs) = default;
	Stage& operator = (const Stage& rhs) = default;

	bool cflg = 0;




	static const int g_map_chip_size;
	static const int g_map_chip_count_width=40;
	static const int g_map_chip_count_height=26;
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

	//�z�u�f�[�^�����Ă������߂̓񎟌��z��(����) 
	MAP_CHIP_ID g_Map[g_map_chip_count_height][g_map_chip_count_width];
	bool g_map_flg[g_map_chip_count_height][g_map_chip_count_width];
	bool g_map_terrain[g_map_chip_count_height][g_map_chip_count_width];
	bool g_map_wall[g_map_chip_count_height][g_map_chip_count_width];
	//MAP_CHIP_ID *g_Map;
	//bool *g_map_flg;
	//bool *g_map_terrain;
	//bool *g_map_wall;
};