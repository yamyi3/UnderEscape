#pragma once
#include "vivid.h"
#include "visual_id.h"
#include "visual/visual.h"
#include<list>
#include <iostream>
#include <vector>

class VisualManager
{
public:
	//インスタンスを生成、取得
	static VisualManager& GetInstance(void);
	//初期化
	void Initialize(void);
	//更新
	void Update(void);
	//描画
	void Draw(void);
	//解放
	void Finalize(void);

	void Input_scroll(vivid::Vector2 s) { scroll = s; }
private:
	using VISUAL_LIST = std::list<Visual*>;
	VISUAL_LIST m_Visual;

	std::vector<std::vector<VISUAL_ID>> g_Map;

	//static const std::string visual_picture_name[(int)VISUAL_ID::MAX];
	//static const int visual_picture_width_size[(int)VISUAL_ID::MAX];
	//static const int visual_picture_height_size[(int)VISUAL_ID::MAX];
	//static const int visual_draw_width_size[(int)VISUAL_ID::MAX];
	//static const int visual_draw_height_size[(int)VISUAL_ID::MAX];
	static const int visual_csv_file_num;

	std::string* visual_csv_file_name;

	vivid::Vector2 scroll;
	int map_chip_size;
	//シングルトンパターンの設定
	VisualManager(void) = default;
	~VisualManager(void) = default;
	VisualManager(const VisualManager& rhs) = default;
	VisualManager& operator = (const VisualManager& rhs) = default;
};