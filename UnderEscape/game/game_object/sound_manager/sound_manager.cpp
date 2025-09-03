#include "sound_manager.h"

const char* CSoundManager::m_sound_file_names[] =
{

};
//インスタンスの取得
CSoundManager& CSoundManager::GetInstance(void)
{
	static CSoundManager instance;

	return instance;
}
//音声データの読み込み
void CSoundManager::Load(void)
{
	for (int i = 0; i < ((int)SOUND_ID::MAX); ++i)
	{
		vivid::LoadSound(m_sound_file_names[i]);
	}
}

//音声データの再生(ボリューム調整付)
void CSoundManager::Play(SOUND_ID id, SOUND_CATEGORY category, bool loop)
{
	vivid::PlaySound(m_sound_file_names[(int)id], loop, m_Volume[(int)category]);
}

//音量の設定
void CSoundManager::SetVolume(SOUND_CATEGORY category, int volume)
{
	m_Volume[(int)category] = volume;
}

//引数カテゴリーの音量の取得(ユーザー向けの数値)
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
