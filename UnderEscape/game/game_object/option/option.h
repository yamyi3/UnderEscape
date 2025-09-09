#pragma once
#include "vivid.h"

//設定リスト
enum class OPTION_LIST
{
	CONTROLL,		//操作説明
	SOUND,			//サウンド設定

	MAX,
};



class COption
{
public:
	//インスタンスの取得
	static COption& GetInstance(void);

	//初期化
	void Initialize(void);

	//更新
	void Update(void);

	//描画
	void Draw(void);

	//解放
	void Finalize(void);

	//音量の数値変換(ユーザー入力0～100をDxLib規定値0～255に変換する)
	void ChangeVolume(void);

	//音量の設定
	void SetVolume(void);

	//コントローラー説明の動作処理
	void ControllerMenu(void);

	//サウンドメニューの動作処理
	void SoundMenu(void);

	//音量調整
	void ChangeSound(int);

	//サウンドメニューの描画処理
	void DrawSoundMenu(void);

	//オプションフラグをgamemainからtrueにする
	void StartOption(void);

	//オプションを閉じる(データ以外初期化する)
	void EndOption(void);

	//オプションフラグの取得
	bool GetOptionFlg(void) { return m_OptionMenu; }
	//サウンドメニューフラグの取得
	bool GetSoundMenuFlg(void) { return m_SoundMenu; }

private:
	bool				m_OptionMenu;		//オプションが起動されているか判断する(trueで起動)
	static const float	m_FrameWidth;		//メニューフレームの幅
	static const float	m_FrameHeight;		//メニューフレームの高さ
	vivid::Vector2		m_FramePos;			//ポーズメニューのフレームの座標
	vivid::Vector2		m_MenuPos[3];		//各メニューの座標
	static const int	m_FontSize;			//メニューのフォントサイズ
	int					m_MenuCursor;	//現在選択しているメニューの記憶

	//->コントローラー操作画面
	bool				m_ControllerMenu;	//コントローラーメニューの起動判断フラグ
	//<-コントローラー操作画面

	//->サウンドメニュー関係
	int					m_ButtonCount;		//ボタンを押し続けている時のカウンタ
	bool				m_SEMenu;			//BGMのボリューム調整メニューフラグ
	bool				m_BGMMenu;			//BGMのボリューム調整メニューフラグ
	bool				m_SoundMenu;		//サウンドメニューの起動判断フラグ
	static const int	m_MaxVolume;		//ユーザー視点の最大音量
	int					m_Volume[2];		//ユーザー設定の任意音量(規定値は最大値)
	vivid::Vector2		m_VolumeMenuPos[3];	//各メニューの座標
	unsigned int		m_VolumeColor[3];	//メニューの色
	std::string			m_VolumeMenuList[3]	//各メニューの表示内容
	{
		"SE",
		"BGM",
		"閉じる"
	};
	int					m_SoundMenuCursor;	//現在選択しているメニューの記憶
	//<-サウンドメニュー関係

	//メニューの一覧(表示用)
	std::string			m_MenuList[3]
	{
		"操作一覧",
		"音量調整",
		"閉じる"
	};

	unsigned int	m_ColorList[3]	//メニューの色リスト
	{
		0xff000000,		//デフォルトカラー
		0xffffff00,		//選択中の色
		0xffff0000		//決定時の色
	};
	unsigned int	m_MenuColor[3];	//各メニューの色
	
	OPTION_LIST option_list;			//設定リスト(一覧)
	
	//->インスタンスの生成
	//コンストラクタ
	COption(void);
	//デストラクタ
	~COption(void);
	//コピーコンストラクタ
	COption(const COption& rhs);
	//代入演算子
	COption& operator = (const COption& rhs);
	//<-インスタンスの生成
};