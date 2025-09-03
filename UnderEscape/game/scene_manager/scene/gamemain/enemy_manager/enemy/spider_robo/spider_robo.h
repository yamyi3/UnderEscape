#pragma once
#include "vivid.h"
#include"..\enemy.h"

class SpiderRobo :public Enemy
{
public:
    // コンストラクタ 
    SpiderRobo(void);

    // デストラクタ 
    ~SpiderRobo(void);

    // 初期化 
    void    Initialize(const vivid::Vector2& position);

    // 描画 
    void    Draw(void);

private:
};