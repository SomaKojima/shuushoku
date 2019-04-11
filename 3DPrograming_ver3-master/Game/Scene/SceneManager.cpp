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

// 初期化処理
void SceneManager::Initialize()
{
}

void SceneManager::Update(DX::StepTimer const& timer)
{
	// シーン変更があった場合
	if (m_currentSceneID != m_changeSceneID)
	{
		ChangeScene();
	}
}

// 描画処理
void SceneManager::Render()
{
}

/// <summary>
/// 終了処理
/// </summary>
void SceneManager::Finalize()
{
}

/// <summary>
/// シーンを変える処理
/// </summary>
void SceneManager::ChangeScene()
{
	
}
