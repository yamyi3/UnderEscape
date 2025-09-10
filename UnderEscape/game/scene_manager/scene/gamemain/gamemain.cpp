#include "gamemain.h"
#include "vivid.h"

#include "character/character.h"
#include "enemy_manager/enemy_manager.h"
#include "stage/stage.h"
#include"item_manager/item_manager.h"
#include"../../scene_manager.h"
#include "../../../game_object/game_object.h"

//Gameobject gameobject;

GameMainScene::GameMainScene(void)
    : change_pos ((vivid::WINDOW_WIDTH / 5.0f * 2.0f), 0.0f)
    , pause_menu(false)
    , frame_pos((vivid::WINDOW_WIDTH / 2.0f - 250.0f), (vivid::WINDOW_HEIGHT / 2.0f - 125.0f))
    , font_size(40)
    , menu_cursor(0)
{
}

void GameMainScene::Initialize(void)
{
    Stage::GetInstance().Initialize();
    Character::GetInstance().Initialize(Stage::GetInstance().GetStartpos());
    EnemyManager::GetInstance().Initialize();
    EnemyManager::GetInstance().GenerateEnemy({ 300.0f, 700.0f }, 300.0f, 500.0f, 1, 700);
    EnemyManager::GetInstance().GenerateEnemy({ 1000.0f, 700.0f }, 1000.0f, 1200.0f, 1, 700);
    COption::GetInstance().Initialize();
    
    ItemManager::GetInstance().Initialize();

    ItemManager::GetInstance().CreateItem(vivid::Vector2{200,600}, ITEM_ID::FLASH_ITEM);

    ItemManager::GetInstance().CreateItem(vivid::Vector2{200,600}, ITEM_ID::FLASH_ITEM);

    for (int i = 0; i < 3; i++)
    {
        menu_pos[i].x = frame_pos.x + ((float)font_size * 2);
        menu_pos[i].y = frame_pos.y + (float)(i * font_size + 40);
        menu_color[i] = color_list[0];
        if (i == 0)
        {
            menu_color[i] = color_list[2];
        }
    }

}

void GameMainScene::Update(void)
{
    Pause();
    if (pause_menu==false && vivid::mouse::Trigger(vivid::mouse::BUTTON_ID::LEFT))
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
    Character::GetInstance().RoundHit(Stage::GetInstance().GetRoundHeight(Character::GetInstance().GetCharapos(), Character::GetInstance().GetCharaWidth(), Character::GetInstance().GetCharaHeight()));
    Character::GetInstance().CheckHit({0,0},0, 0,
    EnemyManager::GetInstance().CheckSearchPlayer(Character::GetInstance().GetCharapos(), Character::GetInstance().GetCharaHeight(), Character::GetInstance().GetCharaWidth(), Character::GetInstance().GetShilding()));

    ItemManager::GetInstance().Update(Character::GetInstance().GetCharapos(), Character::GetInstance().GetCharaWidth(), Character::GetInstance().GetCharaHeight(),
        Stage::GetInstance().GetRoundHeight({ 150,300 }, 15, 15));
    
    }

    if (pause_menu == true)
    {
        PauseMenu();
    }
}

void GameMainScene::Draw(void)
{
    EnemyManager::GetInstance().Draw();
    Stage::GetInstance().Draw();
    Character::GetInstance().Draw();
    
    ItemManager::GetInstance().Draw();

    //if (Character::GetInstance().GetCoverColor() >= 0x1000000)
        //vivid::DrawTexture("data\\Title_背景.png", { 0.0f,0.0f }, Character::GetInstance().GetCoverColor());
    if (pause_menu == true)
    {
        DrawPause();
    }
    if (COption::GetInstance().GetOptionFlg() == true)
    {
        COption::GetInstance().Draw();
    }

#ifdef _DEBUG
    if (COption::GetInstance().GetOptionFlg() == true)
        vivid::DrawText(40, "OptionFlag_ON", vivid::Vector2(((float)(vivid::WINDOW_WIDTH - 400)), 0.0f), 0xff00ffff);
    if (COption::GetInstance().GetOptionFlg() == false)
        vivid::DrawText(40, "OptionFlag_OFF", vivid::Vector2(((float)(vivid::WINDOW_WIDTH - 400)), 0.0f), 0xff00ffff);
    if (COption::GetInstance().GetSoundMenuFlg() == true)
        vivid::DrawText(40, "SoundMenuFlag_ON", vivid::Vector2(((float)(vivid::WINDOW_WIDTH - 450)), 40.0f), 0xff00ffff);
    if (COption::GetInstance().GetSoundMenuFlg() == false)
        vivid::DrawText(40, "SoundMenuFlag_OFF", vivid::Vector2(((float)(vivid::WINDOW_WIDTH - 450)), 40.0f), 0xff00ffff);
#endif
}

void GameMainScene::Finalize(void)
{
    Character::GetInstance().Finalize();
    EnemyManager::GetInstance().Finalize();
    Stage::GetInstance().Finalize();
    COption::GetInstance().Finalize();

    ItemManager::GetInstance().Finalize();
}
void GameMainScene::Pause()
{
    //[P]を押すと止まり再度押すと動く
    if (pause_menu == false && (vivid::keyboard::Trigger(vivid::keyboard::KEY_ID::P) || vivid::controller::Trigger(vivid::controller::DEVICE_ID::PLAYER1, vivid::controller::BUTTON_ID::START)))
    {
        pause_menu = true;
    }
    else if (pause_menu == true && (vivid::keyboard::Trigger(vivid::keyboard::KEY_ID::P) || vivid::controller::Trigger(vivid::controller::DEVICE_ID::PLAYER1, vivid::controller::BUTTON_ID::START)))
    {
        for (int i = 0; i < 3; i++)
        {
            menu_color[i] = color_list[0];
            if (i == 0)
            {
                menu_color[i] = color_list[2];
            }
        }
        menu_cursor = 0;
        pause_menu = false;

        COption::GetInstance().EndOption();
    }
}

void GameMainScene::PauseMenu()
{
    namespace controller = vivid::controller;

    //オプションを起動していなかったら動作する
    if (COption::GetInstance().GetOptionFlg() == false)
    {
        if (controller::Trigger(controller::DEVICE_ID::PLAYER1, controller::BUTTON_ID::A))
        {

            switch (menu_cursor)
            {
            case 0:
                //オプションフラグをtrueにする
                COption::GetInstance().StartOption();
                break;
            case 1:
                //タイトルに戻る
                SceneManager::GetInstance().ChangeScene(SCENE_ID::TITLE);
                break;
            case 2:
                pause_menu = false;
                for (int i = 0; i < 3; i++)
                {
                    menu_color[i] = color_list[0];
                    if (i == 0)
                    {
                        menu_color[i] = color_list[2];
                    }
                }
                menu_cursor = 0;
                break;
            }
        }
        //十字キー上を押したらメニューの選択カーソルがひとつ上に移動する(一番上の場合はその場を維持)
        if (controller::Trigger(controller::DEVICE_ID::PLAYER1, controller::BUTTON_ID::UP))
        {
            if (menu_cursor > 0)
            {
                menu_color[menu_cursor] = color_list[0];
                menu_cursor -= 1;
                menu_color[menu_cursor] = color_list[2];
            }
        }

        //十字キー下を押したらメニューの選択カーソルがひとつ下に移動する(一番下の場合はその場を維持)
        if (controller::Trigger(controller::DEVICE_ID::PLAYER1, controller::BUTTON_ID::DOWN))
        {
            if (0 <= menu_cursor && menu_cursor < 2)
            {
                menu_color[menu_cursor] = color_list[0];
                menu_cursor += 1;
                menu_color[menu_cursor] = color_list[2];
            }
        }
    }

    if (COption::GetInstance().GetOptionFlg() == true)
    {
        COption::GetInstance().Update();
    }
}

//ポーズメニューの描画
void GameMainScene::DrawPause()
{
    vivid::DrawTexture("data\\menu_box.png", frame_pos, 0xffffffff);
    for (int i = 0; i < 3; i++)
    {
        vivid::DrawText(font_size, menu_list[i], menu_pos[i], menu_color[i]);
    }
}

