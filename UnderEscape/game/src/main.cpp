
/*!
 *  @file       main.cpp
 *  @brief      エントリーポイント
 *  @author     Kazuya Maruyama
 *				Toshihito Ohashi
 *  @date       2023/05/08
 *  @version    1.0
 *
 *  Copyright (c) 2013-2023, Toshihito Ohashi. All rights reserved.
 */

#include "vivid.h"
#include "../gamemain/gamemain.h"

GameMain gamemain;
Character character;
Stage stage;

/*!
 *  @brief      描画関数
 */
void
Display(void)
{
    //ゲームメイン更新
    gamemain.Update();
    //ゲームメイン描画
    gamemain.Draw();
}

/*!
 *  @brief      メイン関数
 *
 *  @param[in]  hInst       インスタンスハンドル
 *  @param[in]  hPrevInst   Win16時代の遺物
 *  @param[in]  lpCmdLine   コマンドライン文字列
 *  @param[in]  nCmdShow    ウィンドの表示方法
 *
 *  @return     メイン関数の成否
 */
int WINAPI
WinMain( _In_ HINSTANCE hInst, _In_opt_ HINSTANCE hPrevInst, _In_ LPSTR lpCmdLine, _In_ int nCmdShow )
{
    (void)hPrevInst;
    (void)lpCmdLine;
    (void)nCmdShow;

    // vividライブラリ初期化
    vivid::Initialize( hInst );

    gamemain.Initialize();

    // 更新/描画関数登録
    vivid::DisplayFunction( Display );

    // ゲームループ
    vivid::MainLoop( );

    gamemain.Finalize();

    // vividライブラリ解放
    vivid::Finalize( );
}
