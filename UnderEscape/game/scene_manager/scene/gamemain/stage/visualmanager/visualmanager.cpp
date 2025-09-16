#include "visualmanager.h"
#include "..\..\stage\stage.h"
#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>

//const std::string VisualManager::visual_picture_name[] =
//{
//	"",										//0
//	"data\\�w�i��\\�Y��ȃu���b�N.jpg",		//1
//	"data\\�w�i��\\�Ђъ��ꂽ�u���b�N.jpg",	//2
//	"data\\�w�i��\\��ꂩ���̃u���b�N.jpg",	//3
//	"data\\�w�i��\\�ۂނ����u���b�N.jpg",	//4
//	"data\\�w�i��\\�⒆.png",				//5
//	"data\\�w�i��\\���.png",				//6
//	"data\\�w�i��\\�̂ڂ�K�i.jpg",			//7
//	"data\\�w�i��\\������K�i.jpg",			//8
//	"data\\�w�i��\\�Y��ȕ�.png",			//9
//	"data\\�w�i��\\�Ђъ����.png",			//10
//	"data\\�w�i��\\�p�C�v.png",				//11
//	"data\\�w�i��\\PC.png",					//12
//	"data\\�w�i��\\�{�I.png"				//13
//};
//
//const int VisualManager::visual_picture_width_size[] =
//{
//	0,
//	160,
//	160,
//	160,
//	160,
//	200,
//	200,
//	100,
//	100,
//	40,
//	40,
//	50,
//	200,
//	1000
//};
//const int VisualManager::visual_picture_height_size[] =
//{
//	0,
//	160,
//	160,
//	160,
//	160,
//	200,
//	100,
//	200,
//	200,
//	40,
//	40,
//	50,
//	100,
//	500,
//};
//const int VisualManager::visual_draw_width_size[] =
//{
//	0,
//	100,
//	100,
//	100,
//	100,
//	200,
//	400,
//	100,
//	100,
//	100,
//	100,
//	100,
//	200,
//	200
//};
//const int VisualManager::visual_draw_height_size[] =
//{
//	0,
//	100,
//	100,
//	100,
//	100,
//	200,
//	200,
//	200,
//	200,
//	100,
//	100,
//	100,
//	100,
//	100,
//};

const int VisualManager::visual_csv_file_num = 2;

VisualManager& VisualManager::GetInstance(void)
{
	// TODO: return �X�e�[�g�����g�������ɑ}�����܂�
	static VisualManager instance;
	return instance;
}

void VisualManager::Initialize(void)
{

	const int g_map_chip_count_width = Stage::GetInstance().GetStageWidthCount();
	const int g_map_chip_count_height = Stage::GetInstance().GetStageHeightCount();
	map_chip_size = Stage::GetInstance().GetMapChipSize();

	visual_csv_file_name = new std::string[visual_csv_file_num];

	for (int i = 0; i < visual_csv_file_num; i++)
	{
		std::string s = "data\\BackGround";
		std::string st = ".csv";

		std::ostringstream oss;
		oss << (i+1);   // �����𕶎���X�g���[���ɕϊ�
		s += oss.str(); // string �Ƃ��ĘA��
		s += st;

		visual_csv_file_name[i] = s;
	}

	g_Map.resize(g_map_chip_count_height, std::vector<VISUAL_ID>(g_map_chip_count_width));

	for (int i = 0; i < visual_csv_file_num; i++)
	{
		// �t�@�C���ǂݍ���
		FILE* fp = nullptr;
		fopen_s(&fp, visual_csv_file_name[i].c_str(), "r");
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
		for (int y = 0; y < g_map_chip_count_height; y++)
		{
			for (int x = g_map_chip_count_width - 1; x >= 0; x--)
			{
				if (g_Map[y][x] != VISUAL_ID::EMPTY)
				{
					Visual* visual = nullptr;
					visual = new Visual();
					if (!visual)return;
					visual->Initialize(g_Map[y][x], x, y);

					m_Visual.push_back(visual);
				}
			}
		}
	}


}

void VisualManager::Update(void)
{
}

void VisualManager::Draw(void)
{
	VISUAL_LIST::iterator it = m_Visual.begin();
	VISUAL_LIST::iterator end = m_Visual.end();

	while (it != end)
	{
		(*it)->Draw(scroll);

		++it;
	}
}

void VisualManager::Finalize(void)
{
}
