#pragma once
enum class ITEM_ID
{
	// アイテムのIDを定義
	DUMMY,			//ダミー
	FLASH_ITEM,		//フラッシュアイテム
	SOUND_ITEM,		//音の出るアイテム

	MAX
};

enum class ITEM_STATE
{
	DUMMY,		//ダミー
	PLACE,		//設置
	GET,		//プレイヤー取得
	USE,		//投げられている
	BREAK,		//破壊
};

enum class ITEM_ORBIT
{
	DUMMY,
	MAIN
};
