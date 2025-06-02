#include "title.h"
#include"vivid.h"
#include"../../scene_manager.h" 
//コンストラクタ
TitleScene::TitleScene()
{
    team_time = 0;                //チームロゴの透明、不透明になるまでのカウント
    title_time = 0;                //タイトルロゴの透明、不透明になるまでのカウント
    hold_time = 0;                //チームロゴの表示時間
    color_max_time = 0;                //ロゴ完全に透明、不透明になるまでの時間
    title_color = 0x00000000;       //タイトルロゴの色の管理
    team_color = 0x00000000;       //チームロゴの色の管理
    back_color = 0x00000000;       //背景の色（固定）
    pos = { 0.0f,0.0f };    //背景の位置（原点）
    spos1 = { 0.0f,0.0f };    //START[ENTER]の位置
    spos2 = { 0.0f,0.0f };    //タイトルロゴの位置
    tpos1 = { 0.0f,0.0f };    //チームロゴの位置
    title_sw = false;            //タイトルロゴの透明、不透明の切り替え
    team_sw = false;            //チームロゴの透明、不透明の切り替え
}
//初期化
void TitleScene::Initialize()
{
    hold_time = 100;
    team_time = 0;
    title_time = 0;
    color_max_time = 60;
    title_color = 0x00000000;
    team_color = 0x00000000;
    back_color = 0xffffffff;
    spos1 = { 400.0f,700.0f };
    spos2 = { 28.0f,100.0f };
    tpos1 = { 550.0f,0.0f };
    title_sw = false;
    team_sw = false;
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

        Title = Title_Draw::Title_Logo;
}
//更新
void TitleScene::Update()
{
    switch (Title)
    {
    case TitleScene::Title_Draw::Team_Logo:
        Team_Update();
        break;

    case TitleScene::Title_Draw::Title_Logo:
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
    vivid::DrawTexture("data\\Title_背景.png", pos, back_color);
    switch (Title)
    {
    case TitleScene::Title_Draw::Team_Logo:
        vivid::DrawTexture("data\\TeamLogo.jpg", tpos1, team_color);
        break;

    case TitleScene::Title_Draw::Title_Logo:
        vivid::DrawTexture("data\\Title_背景.png", pos, back_color);
        vivid::DrawTexture("data\\背景イメージ.png", pos, title_color);
        vivid::DrawTexture("data\\Title.webp", spos2, title_color);
        vivid::DrawText(40, "START[ENTER]", spos1, title_color);
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




