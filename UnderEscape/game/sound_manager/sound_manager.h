#pragma once
#include "vivid.h"

//BGM�̃J�e�S���[
enum class SOUND_CATEGORY
{
	BGM,
	SE,

	MAX,
};


//�T�E���hID
enum class SOUND_ID
{
	TITLE_BGM,
	GAMEMAIN_BGM,
	RESUlT_BGM,

	MAX,
};

class CSoundManager
{
public:
	//�C���X�^���X�̎擾
	static CSoundManager& GetInstance(void);

	//�T�E���h�f�[�^�̓ǂݍ���
	void Load(void);

	//�T�E���h�f�[�^�̍Đ�
	void Play(SOUND_ID id, SOUND_CATEGORY category, bool loop = false);

	//���ʂ̐ݒ�
	void SetVolume(SOUND_CATEGORY category, int volume);

	//�����̃J�e�S���[�̉��ʂ̎擾(���[�U�[�������l�ɕϊ�)
	int GetVolume(SOUND_CATEGORY category);
private:
	//�R���X�g���N�^
	CSoundManager(void);

	//�R�s�[�R���X�g���N�^
	CSoundManager(const CSoundManager& rhs);

	//�f�X�g���N�^
	~CSoundManager(void);

	//������Z�q
	CSoundManager& operator = (const CSoundManager& rhs);

	static const char* m_sound_file_names[(int)SOUND_ID::MAX];	//�T�E���h�f�[�^�̃t�@�C����

	int m_Volume[(int)SOUND_CATEGORY::MAX];
};