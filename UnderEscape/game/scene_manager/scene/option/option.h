#pragma once
#include "vivid.h"

//�ݒ胊�X�g
enum class OPTION_LIST
{
	CONTROLL,		//�������
	SOUND,			//�T�E���h�ݒ�

	MAX,
};

class COption
{
public:
	//�C���X�^���X�̎擾
	static COption& GetInstance(void);

	//������
	void Initialize(void);

	//�X�V
	void Update(void);

	//�`��
	void Draw(void);

	//���
	void Finalize(void);

	//���ʂ̐��l�ϊ�(���[�U�[����0�`100��DxLib�K��l0�`255�ɕϊ�����)
	void ChangeVolume(void);

	//���ʂ̐ݒ�
	void SetVolume(void);

	//�R���g���[���[�����̓��쏈��
	void ControllerMenu(void);

	//�T�E���h���j���[�̓��쏈��
	void SoundMenu(void);

private:
	//->�T�E���h�֌W
	static const int	m_MaxVolume;		//���[�U�[���_�̍ő剹��
	int					m_Volume[2];		//���[�U�[�ݒ�̔C�Ӊ���(�K��l�͍ő�l)
	vivid::Vector2		m_VolumeFramePos;	//�|�[�Y���j���[�̃t���[���̍��W
	vivid::Vector2		m_VolumeMenuPos[3];	//�e���j���[�̍��W
	static const int	m_FontSize;			//���j���[�̃t�H���g�T�C�Y
	std::string			m_VolumeMenuList[3]	//�e���j���[�̕\�����e
	{
		"SE",
		"BGM",
		"����"
	};
	int					m_SoundMenuCursor;	//���ݑI�����Ă��郁�j���[�̋L��
	//<-�T�E���h�֌W

	//���j���[�̈ꗗ(�\���p)
	std::string			m_MenuList[3]
	{
		"����ꗗ",
		"���ʒ���",
		"����"
	};

	int					m_MenuCursor;	//���ݑI�����Ă��郁�j���[�̋L��

	unsigned int	m_ColorList[3]	//���j���[�̐F���X�g
	{
		0xff000000,		//�f�t�H���g�J���[
		0xffffff00,		//�I�𒆂̐F
		0xffff0000		//���莞�̐F
	};
	unsigned int	m_MenuColor[3];	//�e���j���[�̐F
	
	OPTION_LIST option_list;			//�ݒ胊�X�g(�ꗗ)
	
	//->�C���X�^���X�̐���
	//�R���X�g���N�^
	COption(void);
	//�f�X�g���N�^
	~COption(void);
	//�R�s�[�R���X�g���N�^
	COption(const COption& rhs);
	//������Z�q
	COption& operator = (const COption& rhs);
	//<-�C���X�^���X�̐���
};