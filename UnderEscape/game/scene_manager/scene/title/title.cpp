#include "title.h"
#include"vivid.h"
#include"../../scene_manager.h" 
//�R���X�g���N�^
TitleScene::TitleScene()
{
    team_time = 0;                //�`�[�����S�̓����A�s�����ɂȂ�܂ł̃J�E���g
    title_time = 0;                //�^�C�g�����S�̓����A�s�����ɂȂ�܂ł̃J�E���g
    hold_time = 0;                //�`�[�����S�̕\������
    color_max_time = 0;                //���S���S�ɓ����A�s�����ɂȂ�܂ł̎���
    title_color = 0x00000000;       //�^�C�g�����S�̐F�̊Ǘ�
    team_color = 0x00000000;       //�`�[�����S�̐F�̊Ǘ�
    back_color = 0x00000000;       //�w�i�̐F�i�Œ�j
    pos = { 0.0f,0.0f };    //�w�i�̈ʒu�i���_�j
    spos1 = { 0.0f,0.0f };    //START[ENTER]�̈ʒu
    spos2 = { 0.0f,0.0f };    //�^�C�g�����S�̈ʒu
    tpos1 = { 0.0f,0.0f };    //�`�[�����S�̈ʒu
    title_sw = false;            //�^�C�g�����S�̓����A�s�����̐؂�ւ�
    team_sw = false;            //�`�[�����S�̓����A�s�����̐؂�ւ�
}
//������
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

        Title = Title_Draw::Title_Logo;
}
//�X�V
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
//�`��
void TitleScene::Draw()
{
    vivid::DrawTexture("data\\Title_�w�i.png", pos, back_color);
    switch (Title)
    {
    case TitleScene::Title_Draw::Team_Logo:
        vivid::DrawTexture("data\\TeamLogo.jpg", tpos1, team_color);
        break;

    case TitleScene::Title_Draw::Title_Logo:
        vivid::DrawTexture("data\\Title_�w�i.png", pos, back_color);
        vivid::DrawTexture("data\\�w�i�C���[�W.png", pos, title_color);
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
//���
void TitleScene::Finalize()
{
}




