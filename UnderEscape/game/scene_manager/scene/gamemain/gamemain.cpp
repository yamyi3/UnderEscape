#include "gamemain.h"

#include "character/character.h"
#include "enemy_manager/enemy_manager.h"
#include "stage/stage.h"
#include "gameobject/gameobject.h"

//Gameobject gameobject;

GameMainScene::GameMainScene(void)
    : change_pos ((vivid::WINDOW_WIDTH / 5.0f * 2.0f), 0.0f)
    ,pause_menu(false)
{
}

void GameMainScene::Initialize(void)
{
    Stage::GetInstance().Initialize();
    Character::GetInstance().Initialize(Stage::GetInstance().GetStartpos());
    EnemyManager::GetInstance().Initialize();
    EnemyManager::GetInstance().GenerateEnemy({ 300.0f, 700.0f }, 300.0f, 500.0f, 1, 700);
    EnemyManager::GetInstance().GenerateEnemy({ 1000.0f, 700.0f }, 1000.0f, 1200.0f, 1, 700);
    Gameobject::GetInstance().Initialize(Stage::GetInstance().GetRoundHeight());
}

void GameMainScene::Update(void)
{
    Pause();
    if (pause_menu==false&&vivid::mouse::Trigger(vivid::mouse::BUTTON_ID::LEFT))
    {
        vivid::Point mpos = vivid::mouse::GetCursorPos();
        vivid::Vector2 mopos;
        mopos.x = mpos.x;
        mopos.y = mpos.y;
        EnemyManager::GetInstance().sound_sensor(mopos, 300);
    }
    if(pause_menu==false)
    { 
    EnemyManager::GetInstance().Update();

    Character::GetInstance().Update();

    Stage::GetInstance().Update();
    Character::GetInstance().Update();
    Character::GetInstance().RoundHit(Stage::GetInstance().GetRoundHeight());
    Character::GetInstance().CheckHit(Stage::GetInstance().GetWallpos(), Stage::GetInstance().GetWallWidth(),Stage::GetInstance().GetWallHeight(),
        EnemyManager::GetInstance().CheckHitPlayer(Character::GetInstance().GetCharapos(), Character::GetInstance().GetCharaHeight(), Character::GetInstance().GetCharaWidth(), Character::GetInstance().GetShilding()));

   

    Gameobject::GetInstance().Update(Character::GetInstance().GetCharapos(), Character::GetInstance().CheckObtainItem(Gameobject::GetInstance().getItemPos(), Gameobject::GetInstance().GetItemCenter(),
        Gameobject::GetInstance().GetItemWidth(), Gameobject::GetInstance().GetItemHeight()), Character::GetInstance().GetCharaWidth(), Character::GetInstance().GetCharaHeight(),
                Character::GetInstance().CheckThrow(), Stage::GetInstance().GetRoundHeight(), Character::GetInstance().checkPut());
    }
}

void GameMainScene::Draw(void)
{
    EnemyManager::GetInstance().Draw();
    Stage::GetInstance().Draw();
    Character::GetInstance().Draw();
    Gameobject::GetInstance().Draw();
}

void GameMainScene::Finalize(void)
{
    Character::GetInstance().Finalize();
    EnemyManager::GetInstance().Finalize();
    Stage::GetInstance().Finalize();
    Gameobject::GetInstance().Finalize();
}
void GameMainScene::Pause()
{
    //[P]ÇâüÇ∑Ç∆é~Ç‹ÇËçƒìxâüÇ∑Ç∆ìÆÇ≠
    if (pause_menu == false && vivid::keyboard::Trigger(vivid::keyboard::KEY_ID::P))
    {
        pause_menu = true;
    }
    else if(pause_menu == true && vivid::keyboard::Trigger(vivid::keyboard::KEY_ID::P))
        pause_menu = false;
}
