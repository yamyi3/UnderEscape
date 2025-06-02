#include "gamemain.h"

GameMainScene::GameMainScene(void)
{
}

void GameMainScene::Initialize(void)
{
    stage.Initialize();
    character.Initialize(stage.GetRoundpos());
    enemy.Initialize({ 300.0f, 700.0f }, 300.0f, 500.0f,1,700);
    gameobject.Initialize(stage.GetRoundpos());
}

void GameMainScene::Update(void)
{
    if (vivid::mouse::Trigger(vivid::mouse::BUTTON_ID::LEFT))
    {
        vivid::Point mpos = vivid::mouse::GetCursorPos();
        vivid::Vector2 mopos;
        mopos.x = mpos.x;
        mopos.y = mpos.y;
        enemy.sound_sensor(mopos, 300);
    }
    enemy.Update();

    stage.Update();
    character.Update();
    character.RoundHit(stage.GetRoundpos());
    character.CheckHit(stage.GetWallpos(), stage.GetWallWidth(), stage.GetWallHeight(), enemy.GetCircleCenterPos(), enemy.GetCircleRadius());

    gameobject.Update(character.GetCharapos(), character.CheckObtainItem(gameobject.getItemPos(), gameobject.GetItemCenter(), gameobject.GetItemWidth(), gameobject.GetItemHeight()), character.GetCharaWidth(), character.GetCharaHeight(), character.CheckThrow(), stage.GetRoundpos(), character.checkPut());

}

void GameMainScene::Draw(void)
{
    enemy.Draw();
    stage.Draw();
    character.Draw();
    gameobject.Draw();
}

void GameMainScene::Finalize(void)
{
    character.Finalize();
    enemy.Finalize();
    stage.Finalize();
    gameobject.Finalize();
}
