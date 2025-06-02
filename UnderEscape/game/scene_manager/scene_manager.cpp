#include"scene_manager.h"
#include"scene//title/title.h"
#include"scene/gamemain/gamemain.h"
#include"scene/result/result.h"
#include"scene/result/GameClear/GameClear.h"
#include"scene/result/GameOver/GameOver.h"

//クラスオブジェクトの取得
SceneManager& SceneManager::GetInstance()
{
	static SceneManager instance;

	return instance;
	// TODO: return ステートメントをここに挿入します
}

//初期化
void SceneManager::Initialize()
{
	//タイトルに切り替え
	ChangeScene(SCENE_ID::TITLE);
}

//更新
void SceneManager::Update()
{
	//シーンの切り替わり確認
	if (m_CurrentSceneID != m_NextSceneID)
		Change();//切り替え関数

	//シーンの更新
	m_Scene->Update();
}

//描画
void SceneManager::Draw()
{
	//シーンの描画
	m_Scene->Draw();
}

//解放
void SceneManager::Finalize()
{
	//シーンの解放
	m_Scene->Finalize();

	//シーンオブジェクトの削除
	delete m_Scene;

	m_Scene = nullptr;

}

//シーンの切り替え(要求)
void SceneManager::ChangeScene(SCENE_ID next_scene)
{
	m_NextSceneID = next_scene;
}

//シーンの切り替え(実際の動作)
void SceneManager::Change()
{
	if (m_Scene != nullptr)
	{
		//現在動いてるシーンを終わらせる
		m_Scene->Finalize();

		delete m_Scene;

		m_Scene = nullptr;
	}
	//新しいシーンを作成する
	switch (m_NextSceneID)
	{
	case SCENE_ID::TITLE:
		m_Scene = new TitleScene();
		break;
	case SCENE_ID::GAMEMAIN:
		m_Scene = new GameMainScene();
		break;
	case SCENE_ID::RESULT:
		m_Scene = new ResultScene();
		break;
	case SCENE_ID::GAMECLEAR:
		m_Scene = new GameClear();
		break;
	case SCENE_ID::GAMEOVER:
		m_Scene = new GameOver();
		break;
	default:
		break;
	}
	//ヌルチェックを行う
	if (m_Scene)
	{
		m_Scene->Initialize();
	}

	//シーンIDを合わせる
	m_CurrentSceneID = m_NextSceneID;

}

//コンストラクタ
SceneManager::SceneManager()
	:m_CurrentSceneID(SCENE_ID::DUMMY)
	, m_NextSceneID(SCENE_ID::DUMMY)
	, m_Scene(nullptr)
{

}
//コピーコンストラクタ
SceneManager::SceneManager(const SceneManager& rhs)
{
	(void)rhs;
}
//ムーブコンストラクタ
SceneManager::SceneManager(SceneManager&& rhs)
{
	(void)rhs;
}

//デストラクタ
SceneManager::~SceneManager()
{
}

//代入演算子
SceneManager& SceneManager::operator=(const SceneManager& rhs)
{
	(void)rhs;

	return *this;

}
