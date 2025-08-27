#pragma once
#include<list>
#include "teleport/teleport.h"
class TeleportManager
{
public:
	//インスタンスの取得
	static TeleportManager& GetInstance();
	// 初期化
	void Initialize(const int);
	// 更新
	void Update();
	// 描画
	void Draw();
	// 開放
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