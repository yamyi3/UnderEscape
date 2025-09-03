#pragma once
#include "vivid.h"

//BGMのカテゴリー
enum class SOUND_CATEGORY
{
	BGM,
	SE,

	MAX,
};


//サウンドID
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
	//インスタンスの取得
	static CSoundManager& GetInstance(void);

	//サウンドデータの読み込み
	void Load(void);

	//サウンドデータの再生
	void Play(SOUND_ID id, SOUND_CATEGORY category, bool loop = false);

	//音量の設定
	void SetVolume(SOUND_CATEGORY category, int volume);

	//引数のカテゴリーの音量の取得(ユーザー向け数値に変換)
	int GetVolume(SOUND_CATEGORY category);
private:
	//コンストラクタ
	CSoundManager(void);

	//コピーコンストラクタ
	CSoundManager(const CSoundManager& rhs);

	//デストラクタ
	~CSoundManager(void);

	//代入演算子
	CSoundManager& operator = (const CSoundManager& rhs);

	static const char* m_sound_file_names[(int)SOUND_ID::MAX];	//サウンドデータのファイル名

	int m_Volume[(int)SOUND_CATEGORY::MAX];
};