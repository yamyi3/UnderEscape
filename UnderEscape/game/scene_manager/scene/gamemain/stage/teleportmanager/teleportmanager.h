#pragma once
#include "teleport/teleport.h"
class TeleportManager
{
public:
	//インスタンスの取得
	static TeleportManager& GetInstance();
	// 初期化
	void Initialize();
	// 更新
	void Update();
	// 描画
	void Draw();
	// 開放
	void Finalize();

private:

	TeleportManager();
	~TeleportManager() = default;
	TeleportManager(const TeleportManager& rhs) = delete;
	TeleportManager& operator=(const TeleportManager& rhs) = delete;
};