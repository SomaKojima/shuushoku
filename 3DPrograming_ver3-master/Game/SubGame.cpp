#include "../pch.h"
#include "SubGame.h"
#include "../Game.h"

#include "Utility/InputManager.h"
#include "Scene/SceneManager.h"

SubGame::SubGame(Game * game)
	:
	m_game(game)
{
}

SubGame::~SubGame()
{
	m_game = nullptr;
}

void SubGame::Initialize()
{
	// シーン管理の初期化
	SceneManager& sceneManager = SceneManager::GetInstace();
	sceneManager.ChangeSceneID(SceneManager::SceneID::Play);
	sceneManager.Initialize();
}

void SubGame::Update(float elapsedTime)
{
	// 入力の更新
	InputManager& inputManager = InputManager::GetInstace();
	inputManager.Update(elapsedTime);

	// シーンの更新
	SceneManager& sceneManager = SceneManager::GetInstace();
	sceneManager.Initialize();
}

void SubGame::Renderer()
{
	// シーンの描画
	SceneManager& sceneManager = SceneManager::GetInstace();
	sceneManager.Render();
}

void SubGame::Finalize()
{
	// シーンの描画
	SceneManager& sceneManager = SceneManager::GetInstace();
	sceneManager.Finalize();
}
