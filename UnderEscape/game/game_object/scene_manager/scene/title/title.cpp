#include "title.h"
#include"vivid.h"
#include"../../scene_manager.h" 
//�R���X�g���N�^

const int               TitleScene::hold_time      = 100;
const int               TitleScene::color_max_time = 60;
const unsigned          TitleScene::back_color     = 0xffffffff;
const vivid::Vector2    TitleScene::back_pos       = { 0.0f,0.0f };
const vivid::Vector2    TitleScene::start_pos      = { 400.0f,700.0f };
const vivid::Vector2    TitleScene::title_pos      = { 240.0f,207.0f };
const vivid::Vector2    TitleScene::team_pos       = { 928.0f,508.0f };



TitleScene::TitleScene()
:team_time      (0)                 //�`�[�����S�̓����A�s�����ɂȂ�܂ł̃J�E���g
,title_time     (0)                 //�^�C�g�����S�̓����A�s�����ɂȂ�܂ł̃J�E���g
,title_color    (0x00000000)        //�^�C�g�����S�̐F�̊Ǘ�
,team_color     (0x00000000)        //�`�[�����S�̐F�̊Ǘ�
,title_sw       (false)             //�^�C�g�����S�̓����A�s�����̐؂�ւ�
,team_sw        (false)             //�`�[�����S�̓����A�s�����̐؂�ւ�
{
}
//������
void TitleScene::Initialize()
{
}
void TitleScene::Title_Update()
{
    title_time += 1;
    //�t�F�[�h�C��
    //60�t���[���Ń^�C�g�����S�����S�Ɍ����
    if (title_time < color_max_time && title_sw == false)
    {
        if ((title_time % 4) == 0)
        {
            title_color += 0x11111111; //�^�C�g�����S�����X�Ɍ����
        }
    }

    //�t�F�[�h�A�E�g
    //ENTER��������60�t���[���Ń^�C�g�����S�����S�ɓ����ɂȂ�
    if ((vivid::keyboard::Trigger(vivid::keyboard::KEY_ID::RETURN)&& title_sw == false) || (vivid::controller::Trigger(vivid::controller::DEVICE_ID::PLAYER1, vivid::controller::BUTTON_ID::A)))
    {
        title_sw = true;
        title_time = 0;
    }
    if (title_time < color_max_time && title_sw == true)
    {
        if ((title_time % 4) == 0)
        {
            if (!(title_color == 0x00000000))
                title_color -= 0x11111111;  //�^�C�g�����S�����X�ɓ����ɂȂ�
        }
    }

}
void TitleScene::Team_Update()
{
    team_time += 1;
    //�t�F�[�h�C��
    //60�t���[���Ń`�[�����S�����S�Ɍ����
    if (team_time < color_max_time && team_sw == false)
    {
        if ((team_time % 4) == 0)
        {
            team_color += 0x11111111;               //�`�[�����S�����X�Ɍ����
        }
    }
    if (team_time >= hold_time && team_sw == false) //�`�[�����S�̕\������
    {
        team_time = 0;
        team_sw = true;
    }

    //�t�F�[�h�A�E�g
    //60�t���[���Ń`�[�����S���S�ɓ����ɂȂ�
    if (team_time < color_max_time && team_sw == true)
    {
        if ((team_time % 4) == 0)
        {
            if (!(team_color == 0x00000000))           //�`�[�����S�����X�ɓ����ɂȂ�
                team_color -= 0x11111111;
        }
    }
    if (team_time >= color_max_time && team_sw == true)

        Title = Opning_Draw::Title_Logo;
}
void TitleScene::Title_Draw()
{
    vivid::DrawTexture("data\\title.png", title_pos, title_color);
    vivid::DrawText(40, "Please[ENTER] or [A]", start_pos, title_color);
}
void TitleScene::Team_Draw()
{
    vivid::DrawTexture("data\\abe.png", team_pos, team_color);
}
//�X�V
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
//�`��
void TitleScene::Draw()
{
    vivid::DrawTexture("data\\Title_�w�i.png", back_pos, back_color);
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
//���
void TitleScene::Finalize()
{
}




