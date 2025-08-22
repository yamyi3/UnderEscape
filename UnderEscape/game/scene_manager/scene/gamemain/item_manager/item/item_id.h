#pragma once
enum class ItemID
{
	// アイテムのIDを定義
	DUMMY ,			//ダミー
	FLASH_ITEM,		//フラッシュアイテム
	SOUND_ITEM,		//音の出るアイテム
	UNKNOWN_ITEM,	//不明なアイテム
};

enum class ITEM_STATE
{
	DUMMY,		//ダミー
	PLACE,		//設置
	GET,		//プレイヤー取得
	USE,		//投げられている
	BREAK,		//破壊
};
