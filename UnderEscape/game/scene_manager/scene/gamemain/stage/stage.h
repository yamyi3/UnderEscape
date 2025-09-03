#pragma once
#include "vivid.h"
#include <iostream>
#include <vector>
#include "teleportmanager/teleportmanager.h"

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
	//
	void MapSizeInitialize(void);
	//�X�e�[�W�̃X�N���[������
	void ScrollStage(void);
	//�e���|�[�g�K�i�̔���擾
	bool GetStairsFlg(vivid::Vector2 cpos) { return TeleportManager::GetInstance().GetTeleportFlg(cpos); }
	//�e���|�[�g�K�i�̍��W�擾
	vivid::Vector2 GetStairs(vivid::Vector2 cpos) { return TeleportManager::GetInstance().StairsTeleport(cpos); }
	//�n�ʍ��W�̃X�^�[�g�n�_�擾
	vivid::Vector2 GetStartpos(void)
	{
		return vivid::Vector2(0.0f, 0.0f);
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

	int GetStageWidthCount() { return g_map_chip_count_width; }
	int GetStageHeightCount() { return g_map_chip_count_height; }


	int GetMapChipSize(){ return g_map_chip_size; }
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
	int g_map_chip_count_width;
	int g_map_chip_count_height;
	// �}�b�v�`�b�v�ԍ���񋓌^�Œ�` 
	enum class MAP_CHIP_ID
	{
		EMPTY,			//0
		GROUND,			//1
		BLOCK,			//2
		RSTAIRS,		//3�^
		LSTAIRS,		//4�_
		WALL,			//5
		ENEMY_AREA,		//6
		R_ENEMY,		//7
		L_ENEMY,		//8
		TPSTAIRS,		//9
		START,			//10
		GOAL,			//11
	};

	//�z�u�f�[�^�����Ă������߂̓񎟌��z��(����) 
	std::vector<std::vector<MAP_CHIP_ID>> g_Map;
	std::vector<std::vector<bool>> g_map_flg;
	std::vector<std::vector<bool>> g_map_terrain;
	std::vector<std::vector<bool>> g_map_wall;

	//MAP_CHIP_ID *g_Map;
	//bool *g_map_flg;
	//bool *g_map_terrain;
	//bool *g_map_wall;
};