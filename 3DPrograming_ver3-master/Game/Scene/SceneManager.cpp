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
	ChangeScene();
}

void SceneManager::Update(float elapsedTime)
{
	if (!m_currentScene)return;
	m_currentScene->GetGameObjectList().Update(elapsedTime);
	// シーン変更があった場合
	if (m_currentSceneID != m_changeSceneID)
	{
		ChangeScene();
	}
}

// 描画処理
void SceneManager::Render()
{
	if (!m_currentScene)return;
	m_currentScene->GetGameObjectList().Render();
}

/// <summary>
/// 終了処理
/// </summary>
void SceneManager::Finalize()
{
	if (!m_currentScene)return;
	m_currentScene->GetGameObjectList().Finalize();
	delete m_currentScene;
	m_currentScene = nullptr;
}

/// <summary>
/// シーンを変える処理
/// </summary>
void SceneManager::ChangeScene()
{
	// 現在のシーンの終了処理
	if (m_currentScene)
	{
		m_currentScene->GetGameObjectList().Finalize();
		delete m_currentScene;
		m_currentScene = nullptr;
	}

	// 新しいシーンの作成
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

	// シーンの更新
	m_currentScene = scene;

	// シーンの初期化
	if (!m_currentScene)return;
	m_currentScene->GetGameObjectList().Initialize();
}
