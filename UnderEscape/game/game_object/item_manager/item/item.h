#pragma once
#include "vivid.h"
#include "item_id.h"
#include "..\..\stage\stage.h"
#include "..\..\character\character.h"
class CItem
{
public:
    // コンストラクタ 
    CItem(ITEM_ID id, ITEM_STATE state, float width, float heght, float radius, float effect_area, int number_of_times);

    // デストラクタ 
    virtual ~CItem(void);

    // 初期化 
    virtual void    Initialize(const vivid::Vector2& position);

    // 更新 
    virtual void    Update(vivid::Vector2 c_pos, float c_width, float c_height, float r_height);

    // 描画 
    virtual void    Draw(void);

    // 解放 
    virtual void    Finalize(void);

    // アイテムの保持
    void CheckObject(vivid::Vector2 c_pos, float c_width, float c_height);

    // 位置の取得 
    vivid::Vector2  GetPosition(void);

    // 位置の設定 
    void            SetPosition(const vivid::Vector2& position);

    // 中心位置の取得 
    vivid::Vector2  GetCenterPosition(void);

    // 半径の取得 
    float           GetRadius(void);

    // アクティブフラグの取得 
    bool            GetActive(void);

    // アクティブフラグの設定 
    void            SetActive(bool active);

    // ユニット識別子取得 
    ITEM_ID   GetBulletCategory(void);

    //アイテムオブジェクトの座標取得
    vivid::Vector2 GetItemPos(void)
    {
        return m_Position;
    }
    //アイテムオブジェクトの中心点の取得
    vivid::Vector2 GetItemCenter(void)
    {
        return m_Center;
    }
    //アイテムオブジェクトの幅取得
    float GetItemWidth(void)
    {
        return m_Width;
    }
    //アイテムオブジェクトの高さ取得
    float GetItemHeight(void)
    {
        return m_Height;
    }
    //アイテムの当たり判定
    void WallCheck(void);

    //アイテムの効果が有効かどうかを取得
    bool GetItemActive(void) { return m_Active; }

    //アイテムの効果範囲を取得
    float GetEffectiveArea(void) { return m_Effect_Area; }

    //アイテムの状態を取得
    ITEM_STATE GetItemState(void) { return m_ItemState; }

    //アイテムのIDを取得
    ITEM_ID GetItemID(void) { return m_ItemID; }

    //キャッチフラグの取得
    bool GetCatchFlg(void) { return m_CatchFlg; }

    //アクティブフラグの取得
    bool IsActive(void) { return m_ActiveFlag; }

    //オブジェクトの削除
    void Destroy(void) { m_ActiveFlag = false; }

    //持っている状態を返す
    bool CanPickUp(void) { return m_Color == m_can_pick_up_color; }

    //拾う動作
    void Found(void);

    //投げる動作
    void Thrown(void);

    //置く動作に移行させる
    void Place(vivid::Vector2 c_pos);

    //置く動作
    void ItemPlace(vivid::Vector2 c_pos);
    bool WallCheck(vivid::Vector2 position);
    bool GroundCheck(vivid::Vector2 position );
    bool CelingCheck(vivid::Vector2 position);
    bool LeftWallCheck(vivid::Vector2 position);
    bool RightWallCheck(vivid::Vector2 position);
protected:

    //プレイヤーが持っている状態の処理
    virtual void GetMove(vivid::Vector2 c_pos, float c_width, float c_height);

    //プレイヤーが投げた後の処理(マウス）
    virtual void UseMove();

    //アイテム軌道の位置セット
    virtual void SetOrbitPosition(vivid::Vector2 position, vivid::Vector2 c_pos);

    static const unsigned int   m_default_color;        //!< デフォルトの色
    static const unsigned int   m_can_pick_up_color;    //!< 取得可能な色
    static const unsigned int   m_picked_up_color;      //!< 取得した色
    static const unsigned int   m_throw_color;		    //!< 投げた色

    static const float          throw_speed;		//アイテムオブジェクトの投げる速度

    float                       m_Ga;				//重力加速度
    int                         m_Width;            //!< 幅 
    int                         m_Height;           //!< 高さ 
    float                       m_Radius;           //!< 半径 
    float                       m_Rotation;         //!< 回転値 

    vivid::Vector2              m_Position;         //!< 位置 
    vivid::Vector2              m_Velocity;         //!< 速度 
    vivid::Vector2              m_Anchor;           //!< 基準点 
    vivid::Vector2              m_Center;			//アイテムオブジェクトの中心点
    vivid::Vector2              m_Scale;            //!< 拡大率 
    vivid::Rect                 m_Rect;             //!< 読み込み範囲 

    unsigned int                m_Color;            //!< 色 
    bool                        m_ActiveFlag;       //!< アクティブフラグ 
    bool 					    m_Active;           //アイテム効果の有効無効
    bool                        m_Place_Flg;        //置く動作に移行するかフラグ

    ITEM_ID                     m_ItemID;  	        //!< アイテムのID
    ITEM_STATE				    m_ItemState;        //!< アイテムの状態

    float                       m_Effect_Area;      //!< アイテムの有効範囲
    vivid::Rect                 m_Effect_Rect;      //!< アイテム効果範囲表示 
    vivid::Vector2              m_Effect_Scale;     //!< 拡大率 
    vivid::Vector2              m_Effect_Anchor;    //!< 拡大率 
    unsigned int                m_Effect_Color;	    //アイテム効果範囲の色

    vivid::Vector2              m_Orbit_Position[10];   //アイテム軌道の位置

    bool                        m_First;           //最初の一回だけtrue
    bool                        m_CatchFlg;			//アイテム取得の判断フラグ
    float                       m_Fall;			    //アイテムオブジェクトの落下速度
    int                         m_Active_Time;	    //アイテムの効果時間	
    int                         m_Number_Of_Times;  //アイテムの効果回数

    bool						ceiling_wall;	    //天井と壁の判定フラグ
    bool 					    left_right_wall;	//左右の壁の判定フラグ
    bool                        ground_wall;		//床の判定フラグ
};