//�^�C�g���V�[��
#pragma once
#include"vivid.h"
#include"../scene.h"

class TitleScene :public IScene
{
public:
    TitleScene();                       //�R���X�g���N�^
    ~TitleScene() = default;            //�f�X�g���N�^      

    void Initialize()override;          //������
    void Update()override;              //�X�V
    void Draw()override;                //�`��
    void Finalize()override;            //���
    void Title_Draw();                  //�^�C�g�����S�̕`��
    void Title_Update();                //�^�C�g�����S�̃t�F�[�h
    void Team_Draw();                   //�`�[�����S�̕`��
    void Team_Update();                 //�`�[�����S�̃t�F�[�h
private:
    vivid::Vector2 back_pos;            //�w�i�̈ʒu�i���_�j
    vivid::Vector2 start_pos1;          //START[ENTER]�̈ʒu
    vivid::Vector2 start_pos2;          //START[ENTER]�̈ʒu
    vivid::Vector2 title_pos;           //�^�C�g�����S�̈ʒu
    vivid::Vector2 team_pos;            //�`�[�����S�̈ʒu

    int team_time;                      //�`�[�����S�̓����A�s�����ɂȂ�܂ł̃J�E���g
    int title_time;                     //�^�C�g�����S�̓����A�s�����ɂȂ�܂ł̃J�E���g
    int hold_time;                      //�`�[�����S�̕\������
    int color_max_time;                 //���S���S�ɓ����A�s�����ɂȂ�܂ł̎���
    unsigned title_color;               //�^�C�g�����S�̐F�̊Ǘ�
    unsigned team_color;                //�`�[�����S�̐F�̊Ǘ�
    unsigned back_color;                //�w�i�̐F�i�Œ�j
    bool team_sw;                       //�`�[�����S�̓����A�s�����̐؂�ւ�
    bool title_sw;                      //�^�C�g�����S�̓����A�s�����̐؂�ւ�

    enum class Opning_Draw              //���S�̕`��
    {
        Team_Logo,
        Title_Logo,
    };
    Opning_Draw Title = Opning_Draw::Team_Logo;
};
