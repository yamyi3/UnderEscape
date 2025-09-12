#include "visual.h"
#include "..\..\stage\stage.h"
#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>

const std::string Visual::visual_picture_name[] =
{
	"",
	"data\\�w�i��\\�Y��ȃu���b�N.jpg",
	"data\\�w�i��\\�Ђъ��ꂽ�u���b�N.jpg",
	"data\\�w�i��\\��ꂩ���̃u���b�N.jpg",
	"data\\�w�i��\\�ۂނ����u���b�N.jpg",
	"data\\�w�i��\\�̂ڂ�K�i.jpg",
	"data\\�w�i��\\������K�i.jpg"
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
	// TODO: return �X�e�[�g�����g�������ɑ}�����܂�
	static Visual instance;
	return instance;
}

void Visual::Initialize(void)
{
	const int g_map_chip_count_width = Stage::GetInstance().GetStageWidthCount();
	const int g_map_chip_count_height = Stage::GetInstance().GetStageHeightCount();
	map_chip_size = Stage::GetInstance().GetMapChipSize();

	g_Map.resize(g_map_chip_count_height, std::vector<VISUAL_ID>(g_map_chip_count_width));

	// �t�@�C���ǂݍ���
	FILE* fp = nullptr;
	fopen_s(&fp, "data\\BackGround.csv", "r");
	fseek(fp, 0, SEEK_END);
	int size = ftell(fp);
	fseek(fp, 0, SEEK_SET);

	char* buf = new char[size + 1];   // +1 �͕�����I�[�p
	fread(buf, size, 1, fp);
	buf[size] = '\0';                 // ������I�[��t�^
	fclose(fp);

	// CSV���
	std::string data(buf);
	delete[] buf;

	std::stringstream ss(data);
	int k = 0;
	int value;

	while (ss >> value) {
		// �z��ɑ���i2������1�����ɒ����Ċi�[�j
		g_Map[k / g_map_chip_count_width][k % g_map_chip_count_width] =
			static_cast<VISUAL_ID>(value);
		++k;

		// ��؂蕶����������ǂݔ�΂�
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
