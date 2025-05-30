#include "stage.h"

Stage::Stage(void)
	: wall_width(200)
	, wall_height(200)
	, wall_color(0xff000000)
{
}

void Stage::Initialize(void)
{
	round_pos = { 0.0f, (vivid::WINDOW_HEIGHT - 300) };
	wall_pos.y = round_pos.y - wall_height;
	wall_pos.x = 400;
}

void Stage::Update(void)
{
}

void Stage::Draw(void)
{
	vivid::DrawTexture("data\\round_box.png", round_pos);
	vivid::DrawTexture("data\\ŽÕ•Á.png", wall_pos, wall_color);
}

void Stage::Finalize(void)
{
}

void Stage::ScrollStage(void)
{

}
