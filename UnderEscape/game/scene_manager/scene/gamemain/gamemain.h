#pragma once
#include "vivid.h"
#include"../scene.h"


class GameMainScene : public IScene
{
public:
	GameMainScene(void);
	~GameMainScene(void) = default;

	void Initialize(void)override;
	void Update(void)override;
	void Draw(void)override;
	void Finalize(void)override;

	bool GameFlg() { return true; }
	void Pause();	//�|�[�Y�Ɉڍs���鏈��

	void PauseMenu();	//�|�[�Y���j���[���̓���A���X�V
	void DrawPause();	//�|�[�Y���j���[�̕`��
private:

	//���@�ړ��ƕǈړ��̐؂�ւ���
	vivid::Vector2	change_pos;
	//�|�[�Y���j���[�̐؂�ւ�[true]�̏ꍇ�͎~�܂�[false]�̏ꍇ�͓���
	bool pause_menu;

	vivid::Vector2	frame_pos;		//���j���[�̃t���[���̍��W
	vivid::Vector2	menu_pos[3];	//�|�[�Y���j���[�̓��e���Ƃ̍��W(�ݒ�A�^�C�g���֖߂�A�|�[�Y����)
	const int		font_size;		//�����̑傫��
	int				menu_cursor;	//�|�[�Y���j���[�̌��ݑI�����Ă���ꏊ
	std::string		menu_list[3] =	//�|�[�Y���j���[�̉��u���p����
	{
		"�Q�[���ݒ�",
		"�^�C�g���֖߂�",
		"����"
	};
	unsigned int	menu_color[3];	//�e���j���[�̐F
	unsigned int	color_list[3] = //���j���[�̕����̐F
	{
		0xff000000,		//�f�t�H���g
		0xffffff00,		//����
		0xffff0000		//�I����Ԃ̈ʒu
	};

};