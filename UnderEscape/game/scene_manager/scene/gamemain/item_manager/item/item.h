#pragma once
#include "vivid.h"
#include "item_id.h"
#include "..\..\stage\stage.h"
#include "..\..\character\character.h"
class Item
{
public:
    // コンストラクタ 
    Item(ITEM_ID id,ITEM_STATE state, float width, float heght,float radius);

    // デストラクタ 
    virtual ~Item(void);

    // 初期化 
    virtual void    Initialize(const vivid::Vector2& position);
    // 更新 
    virtual void    Update(vivid::Vector2 cPos, float cWidth, float cHeight, float rHeight);

    // 描画 
    virtual void    Draw(void);

    // 解放 
    virtual void    Finalize(void);

	// アイテムの保持
    void CheckObject(vivid::Vector2 cPos, float cWidth, float cHeight);

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
        return iPos;
    }
    //アイテムオブジェクトの中心点の取得
    vivid::Vector2 GetItemCenter(void)
    {
        return iCenter;
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
    void WallCheck();
    bool GetItemActive() { return m_Active; }
	float GetEffectiveArea() { return m_Area; } //アイテムの有効範囲を取得

    bool IsActive() const { return m_ActiveFlag; }
    void Destroy() { m_ActiveFlag = false; }
protected:

    //プレイヤーが持っている状態の処理
    virtual void GetMove(vivid::Vector2 cPos, float cWidth, float cHeight);
 
    //プレイヤーが投げた後の処理(マウス）
    virtual void UseMove(vivid::Vector2);

   
    float                       Ga;					//重力加速度
    int                         m_Width;            //!< 幅 
    int                         m_Height;           //!< 高さ 
    float                       m_Radius;           //!< 半径 
    vivid::Vector2              m_Position;         //!< 位置 
    vivid::Vector2              m_Velocity;         //!< 速度 
    unsigned int                m_Color;            //!< 色 
    vivid::Vector2              m_Anchor;           //!< 基準点 
    vivid::Rect                 m_Rect;             //!< 読み込み範囲 
    vivid::Vector2              m_Scale;            //!< 拡大率 
    float                       m_Rotation;         //!< 回転値 
    bool                        m_ActiveFlag;       //!< アクティブフラグ 
    ITEM_ID                     m_ItemID;  	        //!< アイテムのID
	ITEM_STATE				    m_ItemState;        //!< アイテムの状態
    bool                        catchFlg;			//アイテム取得の判断フラグ
	vivid::Vector2              iPos;				//アイテムオブジェクトの座標
	vivid::Vector2              iCenter;			//アイテムオブジェクトの中心点
	static const float          throw_speed;		//アイテムオブジェクトの投げる速度
	float                       item_fall;			//アイテムオブジェクトの落下速度
	unsigned int                iColor;				//アイテムオブジェクトの色
	bool						ceiling_wall;	    //天井と壁の判定フラグ
	bool 					    left_right_wall;	//左右の壁の判定フラグ
	bool                        ground_wall;		//床の判定フラグ
	bool 					    m_Active;           //!< 使用フラグ
	float                       m_Area;             //!< アイテムの有効範囲
};