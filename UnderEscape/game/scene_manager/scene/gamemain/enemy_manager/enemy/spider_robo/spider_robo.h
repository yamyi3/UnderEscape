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
    void Initialize(vivid::Vector2 pos, float L, float R, float vector, float ground);//������
    void Initialize(vivid::Vector2 pos, float L, float R, float vector);//������
    void Initialize(vivid::Vector2 pos, float L, float R);//������
    void Initialize(vivid::Vector2 pos);//������
    void Initialize(void);

    // �`�� 
    void    Draw(vivid::Vector2 scroll);

private:
    std::string enemy_picture_name[(int)eSTATUS::MAX]	//�w偃��{�̉摜�̃t�@�C����
        = {
    "data\\�G�@\\�w偌^\\�ҋ@.png" ,	//Stop			//�ҋ@
    "data\\�G�@\\�w偌^\\���ړ�.png" ,	//Wandering		//�p�j
    "data\\�G�@\\�w偌^\\���ǐ�.png" ,	//Chase			//�ǐ�
    "data\\�G�@\\�w偌^\\�ҋ@.png",		//Vigilance		//�x��
    "data\\�G�@\\�w偌^\\�ҋ@.png" ,	//Surprised		//�X�^��
    "data\\�G�@\\�w偌^\\�ߊl���[�V����.png" };	//Kill

    static const int    m_width;            //!< �� 
    static const int    m_height;           //!< ���� 	
    static const float	m_circle_radius;    //���E�͈�
    static const float  m_move_speed;       //!< �ړ����x 
    static const float  m_chase_move_speed;       //!< �ǐՈړ����x 
    static const float  m_jump_height;
    static const float  m_jump_upspeed;
    static const float  m_jump_downspeed;

};