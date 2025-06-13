#include "title.h"
#include"vivid.h"
#include"../../scene_manager.h" 
//コンストラクタ
TitleScene::TitleScene()
:team_time      (0)                 //チームロゴの透明、不透明になるまでのカウント
,title_time     (0)                 //タイトルロゴの透明、不透明になるまでのカウント
,hold_time      (100)               //チームロゴの表示時間
,color_max_time (60)                //ロゴ完全に透明、不透明になるまでの時間
,title_color    (0x00000000)        //タイトルロゴの色の管理
,team_color     (0x00000000)        //チームロゴの色の管理
,back_color     (0xffffffff)        //背景の色（固定）
,back_pos       { 0.0f,0.0f }       //背景の位置（原点）
,start_pos1     { 400.0f,700.0f }   //START[ENTER]の位置
,start_pos2     { 28.0f,100.0f }    //START[ENTER]の位置
,title_pos      { 28.0f,100.0f }    //タイトルロゴの位置
,team_pos       { 550.0f,0.0f }     //チームロゴの位置
,title_sw       (false)             //タイトルロゴの透明、不透明の切り替え
,team_sw        (false)             //チームロゴの透明、不透明の切り替え
{
}
//初期化
void TitleScene::Initialize()
{
}
void TitleScene::Title_Update()
{
    title_time += 1;
    //フェードイン
    //60フレームでタイトルロゴが完全に現れる
    if (title_time < color_max_time && title_sw == false)
    {
        if ((title_time % 4) == 0)
        {
            title_color += 0x11111111; //タイトルロゴが徐々に現れる
        }
    }

    //フェードアウト
    //ENTERを押すと60フレームでタイトルロゴが完全に透明になる
    if (vivid::keyboard::Trigger(vivid::keyboard::KEY_ID::RETURN))
    {
        title_sw = true;
        title_time = 0;
    }
    if (title_time < color_max_time && title_sw == true)
    {
        if ((title_time % 4) == 0)
        {
            if (!(title_color == 0x00000000))
                title_color -= 0x11111111;  //タイトルロゴが徐々に透明になる
        }
    }

}
void TitleScene::Team_Update()
{
    team_time += 1;
    //フェードイン
    //60フレームでチームロゴが完全に現れる
    if (team_time < color_max_time && team_sw == false)
    {
        if ((team_time % 4) == 0)
        {
            team_color += 0x11111111;               //チームロゴが徐々に現れる
        }
    }
    if (team_time >= hold_time && team_sw == false) //チームロゴの表示時間
    {
        team_time = 0;
        team_sw = true;
    }

    //フェードアウト
    //60フレームでチームロゴ完全に透明になる
    if (team_time < color_max_time && team_sw == true)
    {
        if ((team_time % 4) == 0)
        {
            if (!(team_color == 0x00000000))           //チームロゴが徐々に透明になる
                team_color -= 0x11111111;
        }
    }
    if (team_time >= color_max_time && team_sw == true)

        Title = Opning_Draw::Title_Logo;
}
void TitleScene::Title_Draw()
{
    //vivid::DrawTexture("data\\自機\\背景イメージ.png", back_pos, title_color);
    vivid::DrawTexture("data\\自機\\タイトルロゴ.png", start_pos2, title_color);
    vivid::DrawText(40, "START[ENTER]", start_pos1, title_color);
}
void TitleScene::Team_Draw()
{
    vivid::DrawTexture("data\\ade.png", start_pos2, team_color);
}
//更新
void TitleScene::Update()
{
    switch (Title)
    {
    case TitleScene::Opning_Draw::Team_Logo:
        Team_Update();
        break;

    case TitleScene::Opning_Draw::Title_Logo:
        Title_Update();
        break;
    default:
        break;
    }

    if (title_time == color_max_time && title_sw == true)
        SceneManager::GetInstance().ChangeScene(SCENE_ID::GAMEMAIN);
}
//描画
void TitleScene::Draw()
{
    vivid::DrawTexture("data\\Title_背景.png", back_pos, back_color);
    switch (Title)
    {
    case TitleScene::Opning_Draw::Team_Logo:
        Team_Draw();
        break;

    case TitleScene::Opning_Draw::Title_Logo:
        Title_Draw();
        break;
    default:
        break;
    }
#ifdef _DEBUG
    vivid::DrawText(40, "Title Scene", vivid::Vector2(0.0f, 0.0f));
#endif 
}
//解放
void TitleScene::Finalize()
{
}




