#pragma once
#include<list>
#include "teleport/teleport.h"
class TeleportManager
{
public:
	//�C���X�^���X�̎擾
	static TeleportManager& GetInstance();
	// ������
	void Initialize(const int);
	// �X�V
	void Update();
	// �`��
	void Draw();
	// �J��
	void Finalize();

	vivid::Vector2 StairsTeleport(vivid::Vector2);
private:
	using TELEPORT_LIST = std::list<Teleport*>;
	TELEPORT_LIST m_Teleport;


	//static const int g_map_chip_count_width;
	//static const int g_map_chip_count_height;

	TeleportManager();
	~TeleportManager() = default;
	TeleportManager(const TeleportManager& rhs) = delete;
	TeleportManager& operator=(const TeleportManager& rhs) = delete;
};