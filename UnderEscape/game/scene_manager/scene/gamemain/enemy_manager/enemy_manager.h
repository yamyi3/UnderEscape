#pragma once
#include<list>
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
	void GenerateEnemy(vivid::Vector2 pos, float L, float R, float vector, float ground);
	void GenerateEnemy(vivid::Vector2 pos, float L, float R, float vector);
	void GenerateEnemy(vivid::Vector2 pos, float L, float R);
	void GenerateEnemy(vivid::Vector2 pos);
	void GenerateEnemy();

	bool CheckHitPlayer(const vivid::Vector2& center_pos, int height, int width,bool shielding);
	void sound_sensor(vivid::Vector2 sound_source, float sound_size);	//音の判定



private:
	using ENEMY_LIST = std::list<Enemy*>;
	ENEMY_LIST m_Enemy;
	EnemyManager() = default;
	~EnemyManager() = default;
	EnemyManager(const EnemyManager& rhs) = delete;
	EnemyManager& operator=(const EnemyManager& rhs) = delete;
};