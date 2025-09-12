#include "visual.h"
#include "..\..\stage\stage.h"
#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>

const std::string Visual::visual_picture_name[] =
{
	"",
	"data\\背景類\\綺麗なブロック.jpg",
	"data\\背景類\\ひび割れたブロック.jpg",
	"data\\背景類\\壊れかけのブロック.jpg",
	"data\\背景類\\苔むしたブロック.jpg",
	"data\\背景類\\のぼり階段.jpg",
	"data\\背景類\\くだり階段.jpg"
};

const int Visual::visual_picture_width_size[] =
{
	0,
	160,
	160,
	160,
	160,
	100,
	100,
};
const int Visual::visual_picture_height_size[] =
{
	0,
	160,
	160,
	160,
	160,
	200,
	200,
};
const int Visual::visual_draw_width_size[] =
{
	0,
	100,
	100,
	100,
	100,
	100,
	100,
};
const int Visual::visual_draw_height_size[] =
{
	0,
	100,
	100,
	100,
	100,
	200,
	200,
};

Visual& Visual::GetInstance(void)
{
	// TODO: return ステートメントをここに挿入します
	static Visual instance;
	return instance;
}

void Visual::Initialize(void)
{
	const int g_map_chip_count_width = Stage::GetInstance().GetStageWidthCount();
	const int g_map_chip_count_height = Stage::GetInstance().GetStageHeightCount();
	map_chip_size = Stage::GetInstance().GetMapChipSize();

	g_Map.resize(g_map_chip_count_height, std::vector<VISUAL_ID>(g_map_chip_count_width));

	// ファイル読み込み
	FILE* fp = nullptr;
	fopen_s(&fp, "data\\BackGround.csv", "r");
	fseek(fp, 0, SEEK_END);
	int size = ftell(fp);
	fseek(fp, 0, SEEK_SET);

	char* buf = new char[size + 1];   // +1 は文字列終端用
	fread(buf, size, 1, fp);
	buf[size] = '\0';                 // 文字列終端を付与
	fclose(fp);

	// CSV解析
	std::string data(buf);
	delete[] buf;

	std::stringstream ss(data);
	int k = 0;
	int value;

	while (ss >> value) {
		// 配列に代入（2次元→1次元に直して格納）
		g_Map[k / g_map_chip_count_width][k % g_map_chip_count_width] =
			static_cast<VISUAL_ID>(value);
		++k;

		// 区切り文字が来たら読み飛ばす
		if (ss.peek() == ',' || ss.peek() == '\n') {
			ss.ignore();
		}
	}


}

void Visual::Update(void)
{
}

void Visual::Draw(void)
{
}

void Visual::Finalize(void)
{
}
