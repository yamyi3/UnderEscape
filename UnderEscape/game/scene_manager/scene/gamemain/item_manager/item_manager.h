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
	void Update(vivid::Vector2 cPos, float cWidth, float cHeight, float rHeight,bool check);
	// 描画
	void Draw();
	// 開放
	void Finalize();
	// アイテムの生成
	void CreateItem(vivid::Vector2 position,ITEM_ID id);
	//アイテムのアクティブフラグを取得
	bool GetItemActiveFlag();	
	//アイテムの位置を取得
	vivid::Vector2 GetItemPos();
	//アイテムの有効範囲を取得
	float GetEfectiveArea(ITEM_ID);
	//ITEM_IDを取得
	ITEM_ID GetItemID();
	//ITEM_STATEを取得
	bool GetItemCheck();
private:

	ITEM_ID Item_id;
	using ITEM_LIST = std::list<Item*>;
	ITEM_LIST m_Item;										// アイテムのリスト
	ItemManager() = default;								// コンストラクタ
	ItemManager(const ItemManager&) = delete;				// コピーコンストラクタを削除
	ItemManager& operator=(const ItemManager&) = delete;	// 代入演算子を削除
	~ItemManager() = default;								// デストラクタ
};

