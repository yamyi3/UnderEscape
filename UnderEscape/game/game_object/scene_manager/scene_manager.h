//scene_manager
//シーン管理クラス
#pragma once
#include"vivid.h"
#include"scene/scene_id.h"

class IScene;

class SceneManager
{
public:
	static  SceneManager& GetInstance();

	void Initialize();

	void Update();

	void Draw();

	void Finalize();

	void ChangeScene(SCENE_ID next_scene);

private:
	void Change();

	SceneManager();
	SceneManager(const  SceneManager& rhs);
	SceneManager(SceneManager&& rhs);
	~SceneManager();
	SceneManager& operator=(const SceneManager& rhs);

	IScene* m_Scene;
	SCENE_ID	m_CurrentSceneID;
	SCENE_ID	m_NextSceneID;

};