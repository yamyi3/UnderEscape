#include "sound_manager.h"

const char* CSoundManager::m_sound_file_names[] =
{

};
//�C���X�^���X�̎擾
CSoundManager& CSoundManager::GetInstance(void)
{
	static CSoundManager instance;

	return instance;
}
//�����f�[�^�̓ǂݍ���
void CSoundManager::Load(void)
{
	for (int i = 0; i < ((int)SOUND_ID::MAX); ++i)
	{
		vivid::LoadSound(m_sound_file_names[i]);
	}
}

//�����f�[�^�̍Đ�(�{�����[�������t)
void CSoundManager::Play(SOUND_ID id, SOUND_CATEGORY category, bool loop)
{
	vivid::PlaySound(m_sound_file_names[(int)id], loop, m_Volume[(int)category]);
}

//���ʂ̐ݒ�
void CSoundManager::SetVolume(SOUND_CATEGORY category, int volume)
{
	m_Volume[(int)category] = volume;
}

//�����J�e�S���[�̉��ʂ̎擾(���[�U�[�����̐��l)
int CSoundManager::GetVolume(SOUND_CATEGORY category)
{
	int volume = 0;
	volume = m_Volume[(int)category] / 255 * 100;
	return volume;
}

CSoundManager::CSoundManager(void)
	: m_Volume{255, 255}
{
}

CSoundManager::CSoundManager(const CSoundManager& rhs)
{
	(void)rhs;
}

CSoundManager::~CSoundManager(void)
{
}

CSoundManager& CSoundManager::operator=(const CSoundManager& rhs)
{
	(void)rhs;

	return *this;
}
