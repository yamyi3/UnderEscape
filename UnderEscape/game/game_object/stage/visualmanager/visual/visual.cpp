#include "visual.h"
#include "..\..\..\character\character.h"
#include "..\..\..\stage\stage.h"

const std::string Visual::visual_picture_name[] =
{
	"",										//0
	"data\\”wŒi—Þ\\ãY—í‚ÈƒuƒƒbƒN.jpg",		//1
	"data\\”wŒi—Þ\\‚Ð‚ÑŠ„‚ê‚½ƒuƒƒbƒN.jpg",	//2
	"data\\”wŒi—Þ\\‰ó‚ê‚©‚¯‚ÌƒuƒƒbƒN.jpg",	//3
	"data\\”wŒi—Þ\\‘Û‚Þ‚µ‚½ƒuƒƒbƒN.jpg",	//4
	"data\\”wŒi—Þ\\Šâ’†.png",				//5
	"data\\”wŒi—Þ\\Šâ‘å.png",				//6
	"data\\”wŒi—Þ\\‚Ì‚Ú‚èŠK’i.jpg",			//7
	"data\\”wŒi—Þ\\‚­‚¾‚èŠK’i.jpg",			//8
	"data\\”wŒi—Þ\\ãY—í‚È•Ç.png",			//9
	"data\\”wŒi—Þ\\‚Ð‚ÑŠ„‚ê•Ç.png",			//10
	"data\\”wŒi—Þ\\ƒpƒCƒv.png",				//11
	"data\\”wŒi—Þ\\PC.png",					//12
	"data\\”wŒi—Þ\\–{’I.png",				//13
	"data\\”wŒi—Þ\\oŒû.png",				//14
	"data\\”wŒi—Þ\\”wŒi1.png",				//15
	"data\\”wŒi—Þ\\”wŒi2.png",				//16
	"data\\”wŒi—Þ\\”wŒi3.png",				//17
	"data\\”wŒi—Þ\\ˆÃ‚¢•Ç.png"				//18
};

const int Visual::visual_picture_width_size[] =
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
	40,
	40,
	50,
	200,
	1000,
	600,
	640,
	640,
	640,
	20
};
const int Visual::visual_picture_height_size[] =
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
	40,
	40,
	50,
	100,
	500,
	600,
	215,
	215,
	215,
	20
};
const int Visual::visual_draw_width_size[] =
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
	100,
	100,
	100,
	200,
	200,
	100,
	2083,
	2083,
	2083,
	100
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
	200,
	200,
	100,
	100,
	100,
	100,
	100,
	100,
	700,
	700,
	700,
	100
};

Visual::Visual()
{
}

void Visual::Initialize(VISUAL_ID v_id, int x, int y)
{
	map_chip_size = Stage::GetInstance().GetMapChipSize();
	Visual_ID = v_id;
	Pos = { (float)(x * map_chip_size),(float)((y + 1) * map_chip_size - visual_draw_height_size[(int)Visual_ID]) };
	Rect = { 0,0,visual_picture_width_size[(int)Visual_ID],visual_picture_height_size[(int)Visual_ID] };
	Scale = { (float)visual_draw_width_size[(int)Visual_ID] / (float)visual_picture_width_size[(int)Visual_ID]
			,(float)visual_draw_height_size[(int)Visual_ID] / (float)visual_picture_height_size[(int)Visual_ID] };
	if (Visual_ID == VISUAL_ID::BG1 || Visual_ID == VISUAL_ID::BG2 || Visual_ID == VISUAL_ID::BG3)
		Scale = { (float)visual_draw_height_size[(int)Visual_ID] / (float)visual_picture_height_size[(int)Visual_ID]
				,(float)visual_draw_height_size[(int)Visual_ID] / (float)visual_picture_height_size[(int)Visual_ID] };
}

void Visual::Update(void)
{
}

void Visual::Draw(vivid::Vector2 scroll)
{
		//vivid::Vector2 DrawPos = TpPos[i] + vivid::Vector2{ 0.0f, (float)Stage::GetInstance().GetMapChipSize() } - vivid::Vector2{ 0.0f, tp_HeightSize };
		//if (vivid::WINDOW_WIDTH > DrawPos.x - scroll.x && DrawPos.x - scroll.x + tp_WidthSize > 0)
		//{
		//	vivid::Rect rect = { 0,0,tp_WidthSize,tp_HeightSize };
		//	vivid::DrawTexture(teleport_picture_name[i], DrawPos - scroll, tp_color, rect, { 0,0 }, tp_Scale);
		//}
	if ((vivid::WINDOW_WIDTH > Pos.x - scroll.x && Pos.x - scroll.x + visual_draw_width_size[(int)Visual_ID] > 0)
		&&(vivid::WINDOW_HEIGHT > Pos.y - scroll.y && Pos.y - scroll.y + visual_draw_height_size[(int)Visual_ID] > 0))
	{
		vivid::DrawTexture(visual_picture_name[(int)Visual_ID], Pos - scroll, 0xffffffff, Rect, {0,0}, Scale);
	}
}

void Visual::Finalize(void)
{
}


