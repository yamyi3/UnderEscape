#pragma once
#include<list>
#include <iostream>
#include <vector>
#include "enemy_sheet_id.h"
#include "enemy/enemy.h"
#include "vivid.h"
class EnemyManager
{
public:
	//インスタンスの取得
	static EnemyManager& GetInstance();
	// 初期化
	void Initialize();
	// 更新
	void Update();
	// 描画
	void Draw();
	// 開放
	void Finalize();
	//エネミーの生成
	void GenerateEnemy(ENEMY_ID enemy_id, vivid::Vector2 pos, float L, float R, float vector, float ground);
	void GenerateEnemy(ENEMY_ID enemy_id, vivid::Vector2 pos, float L, float R, float vector);
	void GenerateEnemy(ENEMY_ID enemy_id, vivid::Vector2 pos, float L, float R);
	void GenerateEnemy(ENEMY_ID enemy_id, vivid::Vector2 pos);
	void GenerateEnemy(ENEMY_ID enemy_id);
	void GenerateEnemy(vivid::Vector2 pos, float L, float R, float vector, float ground);
	void GenerateEnemy(vivid::Vector2 pos, float L, float R, float vector);
	void GenerateEnemy(vivid::Vector2 pos, float L, float R);
	void GenerateEnemy(vivid::Vector2 pos);
	void GenerateEnemy();

	void SheetGenerateEnemy(int x, int y, ENEMY_ID enemy_id, float vector);

	bool CheckHitPlayer(const vivid::Vector2& center_pos, int height, int width, bool shielding);
	bool CheckSearchPlayer(const vivid::Vector2& center_pos, int height, int width,bool shielding);
	void sound_sensor(vivid::Vector2 sound_source, float sound_size);	//音の判定


private:
	vivid::Vector2 scroll;
	using ENEMY_LIST = std::list<Enemy*>;
	ENEMY_LIST m_Enemy;
	EnemyManager() = default;
	~EnemyManager() = default;
	EnemyManager(const EnemyManager& rhs) = delete;
	EnemyManager& operator=(const EnemyManager& rhs) = delete;

	std::vector<std::vector<ENEMY_SHEET_ID>> EnemySheet;
};