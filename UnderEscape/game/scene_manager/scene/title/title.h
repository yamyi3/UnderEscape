//タイトルシーン
#pragma once
#include"vivid.h"
#include"../scene.h"

class TitleScene :public IScene
{
public:
    TitleScene();                       //コンストラクタ
    ~TitleScene() = default;            //デストラクタ      

    void Initialize()override;          //初期化
    void Update()override;              //更新
    void Draw()override;                //描画
    void Finalize()override;            //解放
    void Title_Draw();                  //タイトルロゴの描画
    void Title_Update();                //タイトルロゴのフェード
    void Team_Draw();                   //チームロゴの描画
    void Team_Update();                 //チームロゴのフェード
private:
    vivid::Vector2 back_pos;            //背景の位置（原点）
    vivid::Vector2 start_pos1;          //START[ENTER]の位置
    vivid::Vector2 start_pos2;          //START[ENTER]の位置
    vivid::Vector2 title_pos;           //タイトルロゴの位置
    vivid::Vector2 team_pos;            //チームロゴの位置

    int team_time;                      //チームロゴの透明、不透明になるまでのカウント
    int title_time;                     //タイトルロゴの透明、不透明になるまでのカウント
    int hold_time;                      //チームロゴの表示時間
    int color_max_time;                 //ロゴ完全に透明、不透明になるまでの時間
    unsigned title_color;               //タイトルロゴの色の管理
    unsigned team_color;                //チームロゴの色の管理
    unsigned back_color;                //背景の色（固定）
    bool team_sw;                       //チームロゴの透明、不透明の切り替え
    bool title_sw;                      //タイトルロゴの透明、不透明の切り替え

    enum class Opning_Draw              //ロゴの描画
    {
        Team_Logo,
        Title_Logo,
    };
    Opning_Draw Title = Opning_Draw::Team_Logo;
};
