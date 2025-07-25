#include "ground.h"
const std::string Ground::ground_picture_name = "data\\�Օ�.png";
const int Ground::ground_picture_width_size = 100;
const int Ground::ground_picture_height_size = 100;

Ground::Ground()
{
}

void Ground::Initialize(vivid::Vector2 pos, float V, float H)
{
	w_Pos = pos;
	w_HeightSize = V;
	w_WidthSize = H;
	w_Scale = { H / ground_picture_width_size ,V / ground_picture_height_size };
	w_color = 0xffffffff;
}

void Ground::Initialize(vivid::Vector2 pos1, vivid::Vector2 pos2)
{
	vivid::Vector2 pos;
	if (pos1.x < pos2.x) pos.x = pos1.x;
	else pos.x = pos2.x;
	if (pos1.y < pos2.y) pos.y = pos1.y;
	else pos.y = pos2.y;
	float v = abs(pos1.y - pos2.y);
	float h = abs(pos1.x - pos2.x);
	Initialize(pos, v, h);
}

void Ground::Initialize(vivid::Vector2 pos, float V, float H, int color)
{
	w_Pos = pos;
	w_HeightSize = V;
	w_WidthSize = H;
	w_Scale = { H / ground_picture_width_size ,V / ground_picture_height_size };
	w_color = color;
}

void Ground::Initialize(vivid::Vector2 pos1, vivid::Vector2 pos2, int color)
{
	vivid::Vector2 pos;
	if (pos1.x < pos2.x) pos.x = pos1.x;
	else pos.x = pos2.x;
	if (pos1.y < pos2.y) pos.y = pos1.y;
	else pos.y = pos2.y;
	float v = abs(pos1.y - pos2.y);
	float h = abs(pos1.x - pos2.x);
	Initialize(pos, v, h, color);
}

void Ground::Update(void)
{
}

void Ground::Draw(vivid::Vector2 scroll)
{
	if (vivid::WINDOW_WIDTH > w_Pos.x - scroll.x && w_Pos.x - scroll.x + w_WidthSize > 0)
	{
		vivid::Rect rect = { 0,0,w_WidthSize,w_HeightSize };
		vivid::DrawTexture(ground_picture_name, w_Pos - scroll, w_color, rect, { 0,0 }, w_Scale);
	}
}

void Ground::Finalize()
{
}

bool Ground::CheckHitPlayer(const vivid::Vector2& center_c_pos, int ch_height, int ch_width)
{
	if ((w_Pos.x <= center_c_pos.x) && (w_Pos.x + w_WidthSize >= center_c_pos.x + ch_width) && (w_Pos.y <= center_c_pos.y) && (w_Pos.y + w_HeightSize >= center_c_pos.y + ch_height))
	{
		return true;
	}
	else
	{
		return false;
	}
}