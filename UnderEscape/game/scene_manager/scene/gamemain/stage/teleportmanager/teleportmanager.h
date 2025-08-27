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