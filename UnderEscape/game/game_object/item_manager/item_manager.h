#pragma once
#include<list>
#include"vivid.h"
#include"item/item.h"
#include"item/item_id.h"
class ItemManager
{
public:

	// インスタンスの取得
	static ItemManager& GetInstance();
	// 初期化
	void Initialize();
	// 更新
	void Update(vivid::Vector2 cPos, float cWidth, float cHeight, float rHeight);
	// 描画
	void Draw();
	// 開放
	void Finalize();
	// アイテムの生成
	void CreateItem(vivid::Vector2 position, ITEM_ID id);
	//アイテムのアクティブフラグを取得
	bool GetItemActiveFlag();
	//アイテムの位置を取得
	vivid::Vector2 GetItemPos();
	//アイテムの有効範囲を取得
	float GetEfectiveArea();
	//ITEM_IDを取得
	ITEM_ID GetItemID();
	//ITEM_STATEを取得
	bool GetItemCheck();
private:
	bool				priority;			//アイテムの優先フラグ
	float 				effective_area;		//アイテムの有効範囲
	bool				active;				//アイテムのアクティブフラグ
	vivid::Vector2		position;			//アイテムの位置
	ITEM_ID				Item_id;			//アイテムのID
	using ITEM_LIST = std::list<CItem*>;
	ITEM_LIST m_Item;						// アイテムのリスト

	CItem* m_CatchItem;

	//アイテム所持している状態
	void PickupItem(const vivid::Vector2& center_pos);
	//投げる動作に移行
	void ThrowItem(void);
	//置く動作に移行
	void PlaceItem(const vivid::Vector2& c_pos);

	ItemManager();								// コンストラクタ
	ItemManager(const ItemManager&) = delete;				// コピーコンストラクタを削除
	ItemManager& operator=(const ItemManager&) = delete;	// 代入演算子を削除
	~ItemManager() = default;								// デストラクタ
};

