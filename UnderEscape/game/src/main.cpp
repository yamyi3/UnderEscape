
/*!
 *  @file       main.cpp
 *  @brief      �G���g���[�|�C���g
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
 *  @brief      �`��֐�
 */
void
Display(void)
{
    //�Q�[�����C���X�V
    gamemain.Update();
    //�Q�[�����C���`��
    gamemain.Draw();
}

/*!
 *  @brief      ���C���֐�
 *
 *  @param[in]  hInst       �C���X�^���X�n���h��
 *  @param[in]  hPrevInst   Win16����̈╨
 *  @param[in]  lpCmdLine   �R�}���h���C��������
 *  @param[in]  nCmdShow    �E�B���h�̕\�����@
 *
 *  @return     ���C���֐��̐���
 */
int WINAPI
WinMain( _In_ HINSTANCE hInst, _In_opt_ HINSTANCE hPrevInst, _In_ LPSTR lpCmdLine, _In_ int nCmdShow )
{
    (void)hPrevInst;
    (void)lpCmdLine;
    (void)nCmdShow;

    // vivid���C�u����������
    vivid::Initialize( hInst );

    gamemain.Initialize();

    // �X�V/�`��֐��o�^
    vivid::DisplayFunction( Display );

    // �Q�[�����[�v
    vivid::MainLoop( );

    gamemain.Finalize();

    // vivid���C�u�������
    vivid::Finalize( );
}
