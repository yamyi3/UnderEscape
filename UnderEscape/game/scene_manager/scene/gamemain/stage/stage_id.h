#pragma once
// マップチップ番号を列挙型で定義 
enum class MAP_CHIP_ID
{
	EMPTY,			//0
	BLOCK,			//1ブロック
	WALL,			//2遮蔽
	TPSTAIRS,		//3テレポート階段
	START,			//4スタート地点
	GOAL,			//5ゴール地点
};