#include "../../pch.h"
#include "SceneManager.h"
//#include "ScenePlay.h"
//#include "SceneTitle.h"

SceneManager::SceneManager()
	:
	m_currentScene(nullptr),
	m_currentSceneID(Title),
	m_changeSceneID(Title)
{
}

SceneManager::~SceneManager()
{
}

// ����������
void SceneManager::Initialize()
{
	ChangeScene();
}

void SceneManager::Update(float elapsedTime)
{
	if (!m_currentScene)return;
	m_currentScene->GetGameObjectList().Update(elapsedTime);
	// �V�[���ύX���������ꍇ
	if (m_currentSceneID != m_changeSceneID)
	{
		ChangeScene();
	}
}

// �`�揈��
void SceneManager::Render()
{
	if (!m_currentScene)return;
	m_currentScene->GetGameObjectList().Render();
}

/// <summary>
/// �I������
/// </summary>
void SceneManager::Finalize()
{
	if (!m_currentScene)return;
	m_currentScene->GetGameObjectList().Finalize();
	delete m_currentScene;
	m_currentScene = nullptr;
}

/// <summary>
/// �V�[����ς��鏈��
/// </summary>
void SceneManager::ChangeScene()
{
	// ���݂̃V�[���̏I������
	if (m_currentScene)
	{
		m_currentScene->GetGameObjectList().Finalize();
		delete m_currentScene;
		m_currentScene = nullptr;
	}

	// �V�����V�[���̍쐬
	Scene* scene = nullptr;
	switch (m_changeSceneID)
	{
	case SceneManager::Title:
		break;
	case SceneManager::Play:
		break;
	default:
		break;
	}

	// �V�[���̍X�V
	m_currentScene = scene;

	// �V�[���̏�����
	if (!m_currentScene)return;
	m_currentScene->GetGameObjectList().Initialize();
}
