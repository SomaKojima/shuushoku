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
}

void SceneManager::Update(DX::StepTimer const& timer)
{
	// �V�[���ύX���������ꍇ
	if (m_currentSceneID != m_changeSceneID)
	{
		ChangeScene();
	}
}

// �`�揈��
void SceneManager::Render()
{
}

/// <summary>
/// �I������
/// </summary>
void SceneManager::Finalize()
{
}

/// <summary>
/// �V�[����ς��鏈��
/// </summary>
void SceneManager::ChangeScene()
{
	
}
