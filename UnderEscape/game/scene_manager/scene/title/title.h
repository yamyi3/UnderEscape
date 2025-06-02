//タイトルシーン
#pragma once
#include"vivid.h"
#include"../scene.h"

class TitleScene :public IScene
{
public:
    TitleScene();
    ~TitleScene() = default;

    void Initialize()override;
    void Update()override;
    void Draw()override;
    void Finalize()override;
    void Title_Update();
    void Team_Update();

private:
    vivid::Vector2 pos;         //背景の位置（原点）
    vivid::Vector2 spos1;       //START[ENTER]の位置
    vivid::Vector2 spos2;       //タイトルロゴの位置
    vivid::Vector2 tpos1;       //チームロゴの位置

    int team_time;              //チームロゴの透明、不透明になるまでのカウント
    int title_time;             //タイトルロゴの透明、不透明になるまでのカウント
    int hold_time;              //チームロゴの表示時間
    int color_max_time;        //ロゴ完全に透明、不透明になるまでの時間
    unsigned title_color;       //タイトルロゴの色の管理
    unsigned team_color;        //チームロゴの色の管理
    unsigned back_color;        //背景の色（固定）
    bool team_sw;               //チームロゴの透明、不透明の切り替え
    bool title_sw;              //タイトルロゴの透明、不透明の切り替え

    enum class Title_Draw       //ロゴの描画
    {
        Team_Logo,
        Title_Logo,
    };
    Title_Draw Title = Title_Draw::Team_Logo;
};
