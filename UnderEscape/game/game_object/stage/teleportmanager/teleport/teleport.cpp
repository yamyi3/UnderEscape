#include "teleport.h"
#include "..\..\..\character\character.h"
#include "..\..\..\stage\stage.h"

const int Teleport::TpCount = 2;

Teleport::Teleport()
	:tp_Scale{1,1}
	, tp_WidthSize(100)
	, tp_HeightSize(200)
	, tp_color(0xffffffff)
	, teleport_picture_name(nullptr)
{
}

void Teleport::Initialize()
{
	Initialize({ 0,0 }, { 0,0 });
}

void Teleport::Initialize(vivid::Vector2 pos)
{
	Initialize(pos, { 0,0 });
}

void Teleport::Initialize(vivid::Vector2 pos1, vivid::Vector2 pos2)
{
	TpPos[0] = pos1;
	TpPos[1] = pos2;
	ch_height = Character::GetInstance().GetCharaHeight();
	ch_width = Character::GetInstance().GetCharaWidth();
	map_chip_size = Stage::GetInstance().GetMapChipSize();
	if (!teleport_picture_name)
		teleport_picture_name = new std::string[TpCount];
	for (int i = 0; i < TpCount; i++)
		if (i % 2 == 0)
			teleport_picture_name[i] = "data\\”wŒi—Þ\\‚­‚¾‚èŠK’i.jpg";
		else
			teleport_picture_name[i] = "data\\”wŒi—Þ\\‚Ì‚Ú‚èŠK’i.jpg";

}

void Teleport::Update(void)
{
}

void Teleport::Draw(vivid::Vector2 scroll)
{
	for (int i = 0; i < TpCount; i++)
	{
		vivid::Vector2 DrawPos = TpPos[i] + vivid::Vector2{ 0.0f, (float)Stage::GetInstance().GetMapChipSize() } - vivid::Vector2{0.0f, tp_HeightSize};
		if (vivid::WINDOW_WIDTH > DrawPos.x - scroll.x && DrawPos.x - scroll.x + tp_WidthSize > 0)
		{
			vivid::Rect rect = { 0,0,tp_WidthSize,tp_HeightSize };
			vivid::DrawTexture(teleport_picture_name[i], DrawPos - scroll, tp_color, rect, {0,0}, tp_Scale);
		}
	}
}

void Teleport::Finalize(void)
{
}

void Teleport::InputTpPos(vivid::Vector2 pos)
{
	if (TpPos[0].x == 0 && TpPos[0].y == 0)
		TpPos[0] = pos;
	else
		TpPos[1] = pos;
}

bool Teleport::GetTeleportFlg(vivid::Vector2 p_pos)
{
	for (int i = 0; i < TpCount; i++)
	{
		if (TpPos[i].x <= p_pos.x + ch_width&&
			TpPos[i].x+map_chip_size>=p_pos.x&&
			TpPos[i].y<=p_pos.y+ch_height&&
			TpPos[i].y+map_chip_size>=p_pos.y)
		{
			return true;
		}

	}
	return false;
}

vivid::Vector2 Teleport::GetTeleportPos(vivid::Vector2 p_pos)
{
	for (int i = 0; i < TpCount; i++)
	{
		if (TpPos[i].x <= p_pos.x + ch_width &&
			TpPos[i].x + map_chip_size >= p_pos.x &&
			TpPos[i].y <= p_pos.y + ch_height &&
			TpPos[i].y + map_chip_size >= p_pos.y)
		{
			return TpPos[(i-1)*-1];
		}
	}
	return p_pos;
}
