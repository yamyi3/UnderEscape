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

	bool GetTeleportFlg(vivid::Vector2);
	vivid::Vector2 StairsTeleport(vivid::Vector2);

	void Input_scroll(vivid::Vector2 s) { scroll = s; }
private:
	using TELEPORT_LIST = std::list<Teleport*>;
	TELEPORT_LIST m_Teleport;

	vivid::Vector2 scroll;
	int map_chip_size;

	//static const int g_map_chip_count_width;
	//static const int g_map_chip_count_height;

	TeleportManager();
	~TeleportManager() = default;
	TeleportManager(const TeleportManager& rhs) = delete;
	TeleportManager& operator=(const TeleportManager& rhs) = delete;
};