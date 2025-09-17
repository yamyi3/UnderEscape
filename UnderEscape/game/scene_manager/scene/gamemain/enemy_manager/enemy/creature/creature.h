#pragma once
#include "vivid.h"
#include"..\enemy.h"

class Creature :public Enemy
{
public:
    // �R���X�g���N�^ 
    Creature(void);

    // �f�X�g���N�^ 
    ~Creature(void);

    // ������ 
    void Initialize(vivid::Vector2 pos, float L, float R, float vector, float ground);//������
    void Initialize(vivid::Vector2 pos, float L, float R, float vector);//������
    void Initialize(vivid::Vector2 pos, float L, float R);//������
    void Initialize(vivid::Vector2 pos);//������
    void Initialize(void);

    // �`�� 
    void    Draw(vivid::Vector2 scroll);

private:

    static const int e_visibility_width_size;
    static const int e_visibility_height_size;
    std::string enemy_picture_name[(int)eSTATUS::MAX]	//�w偃��{�̉摜�̃t�@�C����
        = {
    "data\\�G�@\\����\\�E�ҋ@.png" ,	//Stop			//�ҋ@
    "data\\�G�@\\����\\�E���s.png" ,	//Wandering		//�p�j
    "data\\�G�@\\����\\�E�ǐ�.png" ,	//Chase			//�ǐ�
    "data\\�G�@\\����\\�E�ҋ@.png",		//Vigilance		//�x��
    "data\\�G�@\\����\\�E�ҋ@.png" ,	//Surprised		//�X�^��
    "data\\�G�@\\����\\�E�ߊl���[�V����.png" };	//Kill

    static const int    m_width;            //!< �� 
    static const int    m_height;           //!< ���� 	
    static const float	m_circle_radius;    //���E�͈�
    static const float  m_move_speed;       //!< �ړ����x 
    static const float  m_chase_move_speed;       //!< �ǐՈړ����x 
    static const float  m_jump_height;
    static const float  m_jump_upspeed;
    static const float  m_jump_downspeed;
    static const bool   viewing_angle;

};