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

	void Pause();			//�|�[�Y�Ɉȍ~���鏈��
	void PauseMenu(void);	//�|�[�Y���j���[�̓���
	void DrawPause(void);	//�|�[�Y���j���[�̕`��

private:

	//���@�ړ��ƕǈړ��̐؂�ւ����W
	vivid::Vector2	change_pos;
	//�|�[�Y���j���[�̐؂�ւ�[true]�̏ꍇ�̓|�[�Y���j���[���N���A[false]�̏ꍇ�̓|�[�Y���j���[�͊J���Ă��Ȃ�
	bool pause_menu;

	vivid::Vector2	frame_pos;		//�|�[�Y���j���[�̃t���[���̍��W
	vivid::Vector2	menu_pos[3];		//�e���j���[�̍��W
	const int		font_size;		//���j���[�̃t�H���g�T�C�Y
	std::string		menu_list[3]	//�e���j���[�̕\�����e
	{
		"�Q�[���ݒ�",
		"�^�C�g���֖߂�",
		"����"
	};
	unsigned int	color_list[3]	//���j���[�̐F���X�g
	{
		0xff000000,		//�f�t�H���g�J���[
		0xffffff00,		//�I�𒆂̐F
		0xffff0000		//���莞�̐F
	};
	unsigned int	menu_color[3];	//�e���j���[�̐F
	int				menu_cursor;	//���ݑI�����Ă��郁�j���[�̋L���p
};