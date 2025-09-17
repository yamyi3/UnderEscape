#pragma once
#include "vivid.h"
#include"..\enemy.h"

class SpiderRobo :public Enemy
{
public:
    // ƒRƒ“ƒXƒgƒ‰ƒNƒ^ 
    SpiderRobo(void);

    // ƒfƒXƒgƒ‰ƒNƒ^ 
    ~SpiderRobo(void);

    // ‰Šú‰» 
    void Initialize(vivid::Vector2 pos, float L, float R, float vector, float ground);//‰Šú‰»
    void Initialize(vivid::Vector2 pos, float L, float R, float vector);//‰Šú‰»
    void Initialize(vivid::Vector2 pos, float L, float R);//‰Šú‰»
    void Initialize(vivid::Vector2 pos);//‰Šú‰»
    void Initialize(void);

    // •`‰æ 
    void    Draw(vivid::Vector2 scroll);

private:

    static const int e_visibility_width_size;
    static const int e_visibility_height_size;

    std::string enemy_picture_name[(int)eSTATUS::MAX]	//’wåƒƒ{‚Ì‰æ‘œ‚Ìƒtƒ@ƒCƒ‹–¼
        = {
    "data\\“G‹@\\’wåŒ^\\‘Ò‹@.png" ,	//Stop			//‘Ò‹@
    "data\\“G‹@\\’wåŒ^\\¶ˆÚ“®.png" ,	//Wandering		//œpœj
    "data\\“G‹@\\’wåŒ^\\¶’ÇÕ.png" ,	//Chase			//’ÇÕ
    "data\\“G‹@\\’wåŒ^\\‘Ò‹@.png",		//Vigilance		//Œx‰ú
    "data\\“G‹@\\’wåŒ^\\‘Ò‹@.png" ,	//Surprised		//ƒXƒ^ƒ“
    "data\\“G‹@\\’wåŒ^\\‰E•ßŠlƒ‚[ƒVƒ‡ƒ“.png" };	//Kill

    static const int    m_width;            //!< • 
    static const int    m_height;           //!< ‚‚³ 	
    static const float	m_circle_radius;    //‹ŠE”ÍˆÍ
    static const float  m_move_speed;       //!< ˆÚ“®‘¬“x 
    static const float  m_chase_move_speed;       //!< ’ÇÕˆÚ“®‘¬“x 
    static const float  m_jump_height;
    static const float  m_jump_upspeed;
    static const float  m_jump_downspeed;
    static const bool   viewing_angle;

};