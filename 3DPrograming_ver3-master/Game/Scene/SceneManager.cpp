#include "../../pch.h"
#include "SceneManager.h"
#include "PlayScene.h"
//#include "SceneTitle.h"

/// <summary>
/// コンストラクタ
/// </summary>
SceneManager::SceneManager()
	:
	m_currentScene(nullptr),
	m_currentSceneID(Title),
	m_changeSceneID(Title)
{
}

/// <summary>
/// デストラクタ
/// </summary>
SceneManager::~SceneManager()
{
}

/// <summary>
/// 初期化処理
/// </summary>
void SceneManager::Initialize()
{
	ChangeScene();
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="elapsedTime"></param>
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

/// <summary>
/// 描画処理
/// </summary>
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
		scene = new PlayScene();
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
