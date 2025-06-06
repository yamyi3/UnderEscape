#include "gameobject.h"

Gameobject::Gameobject(void)
	: breakFlg(false)
	, item_fall(1.0f)
{
}

void Gameobject::Initialize(float rHeight)
{
	iPos.x = 800.0f;
	iPos.y = rHeight - item_height;
	iColor = 0xffffffff;
	iCenter.x = (iPos.x + item_width) / 2;
	iCenter.y = (iPos.y + item_height) / 2;
}

void Gameobject::Update(vivid::Vector2 cPos, bool cFlg, float cWidth, float cHeight, bool cThrowFlg, float rHeight, bool cPutFlg)
{
	if (cFlg)
	{
		item_state = ITEM_STATE::GET;
	}

	if (cThrowFlg)
	{
		item_state = ITEM_STATE::THROW;
	}
	if (cPutFlg)
	{
		item_state = ITEM_STATE::PLACE;
	}

	switch (item_state)
	{
	case ITEM_STATE::GET:
		GetMove(cPos, cWidth, cHeight);
		break;
	case ITEM_STATE::THROW:
		ThrowMove3(rHeight, cPos);
		break;
	case ITEM_STATE::PLACE:
		PutMove(rHeight);
	}

}

void Gameobject::Draw(void)
{
	vivid::DrawTexture("data\\ball.png", iPos, iColor);
}

void Gameobject::Finalize(void)
{
}

//アイテムと自機が接触して壊れた(音が鳴る判定に入った)時の処理
void Gameobject::BreakMove(void)
{

}

//自機がアイテムを所持している状態の時の処理
void Gameobject::GetMove(vivid::Vector2 cPos, float cWidth, float cHeight)
{
	catchFlg = true;

	if (catchFlg)
	{
		iPos.x = cPos.x + cWidth;
		iPos.y = cPos.y + (cHeight / 2);
		iCenter.x = (iPos.x + item_width) / 2;
		iCenter.y = (iPos.y + item_height) / 2;
		iColor = 0xffff00ff;
	}
	Ga = 1.0;
	V = 0.0;
}

void Gameobject::PutMove(float rHeight)
{
	if (iPos.y + item_height < rHeight)
		iPos.y += 7.5;
	else
	{
		iPos.y = rHeight - item_height;
	}
	iColor = 0xffffffff;
}

//自機がアイテムを投げた時の処理マウスのポインタ参照(山なり）
void Gameobject::ThrowMove3(float rHeight, vivid::Vector2 c_pos)
{

	if (catchFlg == true && vivid::keyboard::Trigger(vivid::keyboard::KEY_ID::C))
	{
		Mouse.x = (vivid::mouse::GetCursorPos().x) - c_pos.x;
		Mouse.y = c_pos.y - vivid::mouse::GetCursorPos().y;
	}
	catchFlg = false;

	V = -(Mouse.y / Yspeed);

	if (iPos.y + item_height < rHeight)
	{
		iPos.x += Mouse.x / Xspeed;
		iPos.y += V + (item_fall * Ga);
		iColor = 0xff00ffff;
	}

	if (iPos.y + item_height >= rHeight)
	{
		iPos.y = rHeight - item_height;
		item_state = ITEM_STATE::PLACE;
		iColor = 0xffffffff;
	}
	Ga += 0.981;

}