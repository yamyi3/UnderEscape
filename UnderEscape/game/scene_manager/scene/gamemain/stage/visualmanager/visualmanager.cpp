#include "visualmanager.h"
#include "..\..\stage\stage.h"
#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>

const std::string VisualManager::visual_picture_name[] =
{
	"",
	"data\\”wŒi—Ş\\ãY—í‚ÈƒuƒƒbƒN.jpg",
	"data\\”wŒi—Ş\\‚Ğ‚ÑŠ„‚ê‚½ƒuƒƒbƒN.jpg",
	"data\\”wŒi—Ş\\‰ó‚ê‚©‚¯‚ÌƒuƒƒbƒN.jpg",
	"data\\”wŒi—Ş\\‘Û‚Ş‚µ‚½ƒuƒƒbƒN.jpg",
	"data\\”wŒi—Ş\\Šâ’†.png",
	"data\\”wŒi—Ş\\Šâ‘å.png",
	"data\\”wŒi—Ş\\‚Ì‚Ú‚èŠK’i.jpg",
	"data\\”wŒi—Ş\\‚­‚¾‚èŠK’i.jpg",
	"data\\”wŒi—Ş\\PC.png",
	"data\\”wŒi—Ş\\–{’I.png"
};

const int VisualManager::visual_picture_width_size[] =
{
	0,
	160,
	160,
	160,
	160,
	200,
	200,
	100,
	100,
	200,
	1000
};
const int VisualManager::visual_picture_height_size[] =
{
	0,
	160,
	160,
	160,
	160,
	200,
	100,
	200,
	200,
	100,
	500,
};
const int VisualManager::visual_draw_width_size[] =
{
	0,
	100,
	100,
	100,
	100,
	200,
	400,
	100,
	100,
	200,
	200
};
const int VisualManager::visual_draw_height_size[] =
{
	0,
	100,
	100,
	100,
	100,
	200,
	200,
	200,
	200,
	100,
	100,
};

VisualManager& VisualManager::GetInstance(void)
{
	// TODO: return ƒXƒe[ƒgƒƒ“ƒg‚ğ‚±‚±‚É‘}“ü‚µ‚Ü‚·
	static VisualManager instance;
	return instance;
}

void VisualManager::Initialize(void)
{
	const int g_map_chip_count_width = Stage::GetInstance().GetStageWidthCount();
	const int g_map_chip_count_height = Stage::GetInstance().GetStageHeightCount();
	map_chip_size = Stage::GetInstance().GetMapChipSize();

	g_Map.resize(g_map_chip_count_height, std::vector<VISUAL_ID>(g_map_chip_count_width));

	// ƒtƒ@ƒCƒ‹“Ç‚İ‚İ
	FILE* fp = nullptr;
	fopen_s(&fp, "data\\BackGround.csv", "r");
	fseek(fp, 0, SEEK_END);
	int size = ftell(fp);
	fseek(fp, 0, SEEK_SET);

	char* buf = new char[size + 1];   // +1 ‚Í•¶š—ñI’[—p
	fread(buf, size, 1, fp);
	buf[size] = '\0';                 // •¶š—ñI’[‚ğ•t—^
	fclose(fp);

	// CSV‰ğÍ
	std::string data(buf);
	delete[] buf;

	std::stringstream ss(data);
	int k = 0;
	int value;

	while (ss >> value) {
		// ”z—ñ‚É‘ã“üi2ŸŒ³¨1ŸŒ³‚É’¼‚µ‚ÄŠi”[j
		g_Map[k / g_map_chip_count_width][k % g_map_chip_count_width] =
			static_cast<VISUAL_ID>(value);
		++k;

		// ‹æØ‚è•¶š‚ª—ˆ‚½‚ç“Ç‚İ”ò‚Î‚·
		if (ss.peek() == ',' || ss.peek() == '\n') {
			ss.ignore();
		}
	}


}

void VisualManager::Update(void)
{
}

void VisualManager::Draw(void)
{
}

void VisualManager::Finalize(void)
{
}
