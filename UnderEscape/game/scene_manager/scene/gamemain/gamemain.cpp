#include "gamemain.h"

GameMainScene::GameMainScene(void)
{
}

void GameMainScene::Initialize(void)
{
    stage.Initialize();
    character.Initialize(stage.GetRoundpos());
    enemy.Initialize();
    gameobject.Initialize(stage.GetRoundpos());
}

void GameMainScene::Update(void)
{
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
