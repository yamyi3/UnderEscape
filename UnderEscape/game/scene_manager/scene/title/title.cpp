#include "title.h"
#include"vivid.h"
#include"../../scene_manager.h" 
//�R���X�g���N�^
TitleScene::TitleScene()
:team_time      (0)                 //�`�[�����S�̓����A�s�����ɂȂ�܂ł̃J�E���g
,title_time     (0)                 //�^�C�g�����S�̓����A�s�����ɂȂ�܂ł̃J�E���g
,hold_time      (100)               //�`�[�����S�̕\������
,color_max_time (60)                //���S���S�ɓ����A�s�����ɂȂ�܂ł̎���
,title_color    (0x00000000)        //�^�C�g�����S�̐F�̊Ǘ�
,team_color     (0x00000000)        //�`�[�����S�̐F�̊Ǘ�
,back_color     (0xffffffff)        //�w�i�̐F�i�Œ�j
,back_pos       { 0.0f,0.0f }       //�w�i�̈ʒu�i���_�j
,start_pos1     { 400.0f,700.0f }   //START[ENTER]�̈ʒu
,start_pos2     { 28.0f,100.0f }    //START[ENTER]�̈ʒu
,title_pos      { 28.0f,100.0f }    //�^�C�g�����S�̈ʒu
,team_pos       { 550.0f,0.0f }     //�`�[�����S�̈ʒu
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
    //vivid::DrawTexture("data\\���@\\�w�i�C���[�W.png", back_pos, title_color);
    vivid::DrawTexture("data\\���@\\�^�C�g�����S.png", start_pos2, title_color);
    vivid::DrawText(40, "START[ENTER]", start_pos1, title_color);
}
void TitleScene::Team_Draw()
{
    vivid::DrawTexture("data\\ade.png", start_pos2, team_color);
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




