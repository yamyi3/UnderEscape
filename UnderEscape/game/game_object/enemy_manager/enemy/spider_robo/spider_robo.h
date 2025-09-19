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
    void Initialize(vivid::Vector2 pos, float L, float R, float vector, float ground);//初期化
    void Initialize(vivid::Vector2 pos, float L, float R, float vector);//初期化
    void Initialize(vivid::Vector2 pos, float L, float R);//初期化
    void Initialize(vivid::Vector2 pos);//初期化
    void Initialize(void);

    // 描画 
    void    Draw(vivid::Vector2 scroll);

private:

    static const int e_visibility_width_size;
    static const int e_visibility_height_size;

    std::string enemy_picture_name[(int)eSTATUS::MAX]	//蜘蛛ロボの画像のファイル名
        = {
    "data\\敵機\\蜘蛛型\\待機.png" ,	//Stop			//待機
    "data\\敵機\\蜘蛛型\\左移動.png" ,	//Wandering		//徘徊
    "data\\敵機\\蜘蛛型\\左追跡.png" ,	//Chase			//追跡
    "data\\敵機\\蜘蛛型\\待機.png",		//Vigilance		//警戒
    "data\\敵機\\蜘蛛型\\待機.png" ,	//Surprised		//驚く
    "data\\敵機\\蜘蛛型\\待機.png" ,	//STUN  		//スタン
    "data\\敵機\\蜘蛛型\\右捕獲モーション.png" };	//Kill

    static const int    m_width;            //!< 幅 
    static const int    m_height;           //!< 高さ 	
    static const int    m_stun_time;        //!< スタン時間
    static const float	m_circle_radius;    //視界範囲
    static const float  m_move_speed;       //!< 移動速度 
    static const float  m_chase_move_speed;       //!< 追跡移動速度 
    static const float  m_jump_height;
    static const float  m_jump_upspeed;
    static const float  m_jump_downspeed;
    static const bool   viewing_angle;

};