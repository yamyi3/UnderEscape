#include "visual.h"
#include "..\..\..\character\character.h"
#include "..\..\..\stage\stage.h"

const std::string Visual::visual_picture_name[] =
{
	"",										//0
	"data\\�w�i��\\�Y��ȃu���b�N.jpg",		//1
	"data\\�w�i��\\�Ђъ��ꂽ�u���b�N.jpg",	//2
	"data\\�w�i��\\��ꂩ���̃u���b�N.jpg",	//3
	"data\\�w�i��\\�ۂނ����u���b�N.jpg",	//4
	"data\\�w�i��\\�⒆.png",				//5
	"data\\�w�i��\\���.png",				//6
	"data\\�w�i��\\�̂ڂ�K�i.jpg",			//7
	"data\\�w�i��\\������K�i.jpg",			//8
	"data\\�w�i��\\�Y��ȕ�.png",			//9
	"data\\�w�i��\\�Ђъ����.png",			//10
	"data\\�w�i��\\�p�C�v.png",				//11
	"data\\�w�i��\\PC.png",					//12
	"data\\�w�i��\\�{�I.png",				//13
	"data\\�w�i��\\�o��.png",				//14
	"data\\�w�i��\\�w�i1.png",				//15
	"data\\�w�i��\\�w�i2.png",				//16
	"data\\�w�i��\\�w�i3.png",				//17
	"data\\�w�i��\\�Â���.png"				//18
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


