#include"scene_manager.h"
#include"scene//title/title.h"
#include"scene/gamemain/gamemain.h"
#include"scene/result/result.h"
#include"scene/result/GameClear/GameClear.h"
#include"scene/result/GameOver/GameOver.h"

//�N���X�I�u�W�F�N�g�̎擾
SceneManager& SceneManager::GetInstance()
{
	static SceneManager instance;

	return instance;
	// TODO: return �X�e�[�g�����g�������ɑ}�����܂�
}

//������
void SceneManager::Initialize()
{
	//�^�C�g���ɐ؂�ւ�
	ChangeScene(SCENE_ID::TITLE);
}

//�X�V
void SceneManager::Update()
{
	//�V�[���̐؂�ւ��m�F
	if (m_CurrentSceneID != m_NextSceneID)
		Change();//�؂�ւ��֐�

	//�V�[���̍X�V
	m_Scene->Update();
}

//�`��
void SceneManager::Draw()
{
	//�V�[���̕`��
	m_Scene->Draw();
}

//���
void SceneManager::Finalize()
{
	//�V�[���̉��
	m_Scene->Finalize();

	//�V�[���I�u�W�F�N�g�̍폜
	delete m_Scene;

	m_Scene = nullptr;

}

//�V�[���̐؂�ւ�(�v��)
void SceneManager::ChangeScene(SCENE_ID next_scene)
{
	m_NextSceneID = next_scene;
}

//�V�[���̐؂�ւ�(���ۂ̓���)
void SceneManager::Change()
{
	if (m_Scene != nullptr)
	{
		//���ݓ����Ă�V�[�����I��点��
		m_Scene->Finalize();

		delete m_Scene;

		m_Scene = nullptr;
	}
	//�V�����V�[�����쐬����
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
	//�k���`�F�b�N���s��
	if (m_Scene)
	{
		m_Scene->Initialize();
	}

	//�V�[��ID�����킹��
	m_CurrentSceneID = m_NextSceneID;

}

//�R���X�g���N�^
SceneManager::SceneManager()
	:m_CurrentSceneID(SCENE_ID::DUMMY)
	, m_NextSceneID(SCENE_ID::DUMMY)
	, m_Scene(nullptr)
{

}
//�R�s�[�R���X�g���N�^
SceneManager::SceneManager(const SceneManager& rhs)
{
	(void)rhs;
}
//���[�u�R���X�g���N�^
SceneManager::SceneManager(SceneManager&& rhs)
{
	(void)rhs;
}

//�f�X�g���N�^
SceneManager::~SceneManager()
{
}

//������Z�q
SceneManager& SceneManager::operator=(const SceneManager& rhs)
{
	(void)rhs;

	return *this;

}
