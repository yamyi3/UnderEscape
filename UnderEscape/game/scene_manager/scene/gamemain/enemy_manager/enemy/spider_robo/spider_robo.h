#pragma once
#include "vivid.h"
#include"..\enemy.h"

class SpiderRobo :public Enemy
{
public:
    // �R���X�g���N�^ 
    SpiderRobo(void);

    // �f�X�g���N�^ 
    ~SpiderRobo(void);

    // ������ 
    void    Initialize(const vivid::Vector2& position);

    // �`�� 
    void    Draw(void);

private:
};