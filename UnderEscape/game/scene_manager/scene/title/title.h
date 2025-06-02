//�^�C�g���V�[��
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
    vivid::Vector2 pos;         //�w�i�̈ʒu�i���_�j
    vivid::Vector2 spos1;       //START[ENTER]�̈ʒu
    vivid::Vector2 spos2;       //�^�C�g�����S�̈ʒu
    vivid::Vector2 tpos1;       //�`�[�����S�̈ʒu

    int team_time;              //�`�[�����S�̓����A�s�����ɂȂ�܂ł̃J�E���g
    int title_time;             //�^�C�g�����S�̓����A�s�����ɂȂ�܂ł̃J�E���g
    int hold_time;              //�`�[�����S�̕\������
    int color_max_time;        //���S���S�ɓ����A�s�����ɂȂ�܂ł̎���
    unsigned title_color;       //�^�C�g�����S�̐F�̊Ǘ�
    unsigned team_color;        //�`�[�����S�̐F�̊Ǘ�
    unsigned back_color;        //�w�i�̐F�i�Œ�j
    bool team_sw;               //�`�[�����S�̓����A�s�����̐؂�ւ�
    bool title_sw;              //�^�C�g�����S�̓����A�s�����̐؂�ւ�

    enum class Title_Draw       //���S�̕`��
    {
        Team_Logo,
        Title_Logo,
    };
    Title_Draw Title = Title_Draw::Team_Logo;
};
