#include "visual.h"
#include "..\..\..\character\character.h"
#include "..\..\..\stage\stage.h"


Visual::Visual()
{
}

void Visual::Initialize()
{

	map_chip_size = Stage::GetInstance().GetMapChipSize();
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
}

void Visual::Finalize(void)
{
}


