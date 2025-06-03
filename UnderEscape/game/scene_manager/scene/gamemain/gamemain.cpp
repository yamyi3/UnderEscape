#include "gamemain.h"

#include "character/character.h"
#include "enemy/enemy.h"
#include "stage/stage.h"
#include "gameobject/gameobject.h"

Enemy enemy;
Gameobject gameobject;

GameMainScene::GameMainScene(void)
    : change_pos ((vivid::WINDOW_WIDTH / 5.0f * 2.0f), 0.0f)
{
}

void GameMainScene::Initialize(void)
{
    Stage::GetInstance().Initialize();
    Character::GetInstance().Initialize(Stage::GetInstance().GetRoundpos());
    enemy.Initialize({ 300.0f, 700.0f }, 300.0f, 500.0f,1,700);
    gameobject.Initialize(Stage::GetInstance().GetRoundpos());
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

    Stage::GetInstance().Update();
    Character::GetInstance().Update();
    Character::GetInstance().RoundHit(Stage::GetInstance().GetRoundpos());
    Character::GetInstance().CheckHit(Stage::GetInstance().GetWallpos(), Stage::GetInstance().GetWallWidth(),
                Stage::GetInstance().GetWallHeight(), enemy.GetCircleCenterPos(), enemy.GetCircleRadius());

    gameobject.Update(Character::GetInstance().GetCharapos(), Character::GetInstance().CheckObtainItem(gameobject.getItemPos(), gameobject.GetItemCenter(),
                gameobject.GetItemWidth(), gameobject.GetItemHeight()), Character::GetInstance().GetCharaWidth(), Character::GetInstance().GetCharaHeight(), 
                Character::GetInstance().CheckThrow(), Stage::GetInstance().GetRoundpos(), Character::GetInstance().checkPut());

}

void GameMainScene::Draw(void)
{
    enemy.Draw();
    Stage::GetInstance().Draw();
    Character::GetInstance().Draw();
    gameobject.Draw();
}

void GameMainScene::Finalize(void)
{
    Character::GetInstance().Finalize();
    enemy.Finalize();
    Stage::GetInstance().Finalize();
    gameobject.Finalize();
}
