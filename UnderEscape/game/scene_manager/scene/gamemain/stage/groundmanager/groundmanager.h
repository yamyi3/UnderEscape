#pragma once
#include<list>
#include "vivid.h"
#include"ground/ground.h"

class GroundManager
{
public:
	//�C���X�^���X�̎擾
	static GroundManager& GetInstance();
	// ������
	void Initialize();
	// �X�V
	void Update();
	// �`��
	void Draw();
	// �J��
	void Finalize();

	bool CheckHitPlayer(const vivid::Vector2& center_pos, int height, int width);

	void GenerateGround(vivid::Vector2 pos, float V, float H);
	void GenerateGround(vivid::Vector2 pos1, vivid::Vector2 pos2);
	void GenerateGround(vivid::Vector2 pos, float V, float H, int color);
	void GenerateGround(vivid::Vector2 pos1, vivid::Vector2 pos2, int color);
	void Input_scroll(float s) { scroll = s; }
private:
	using GROUND_LIST = std::list<Ground*>;
	GROUND_LIST m_Ground;
	float scroll;

	GroundManager();
	~GroundManager() = default;
	GroundManager(const GroundManager& rhs) = delete;
	GroundManager& operator=(const GroundManager& rhs) = delete;
};
