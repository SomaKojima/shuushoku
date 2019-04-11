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
	// �V�[���Ǘ��̏�����
	SceneManager& sceneManager = SceneManager::GetInstace();
	sceneManager.ChangeSceneID(SceneManager::SceneID::Play);
	sceneManager.Initialize();
}

void SubGame::Update(float elapsedTime)
{
	// ���͂̍X�V
	InputManager& inputManager = InputManager::GetInstace();
	inputManager.Update(elapsedTime);

	// �V�[���̍X�V
	SceneManager& sceneManager = SceneManager::GetInstace();
	sceneManager.Initialize();
}

void SubGame::Renderer()
{
	// �V�[���̕`��
	SceneManager& sceneManager = SceneManager::GetInstace();
	sceneManager.Render();
}

void SubGame::Finalize()
{
	// �V�[���̕`��
	SceneManager& sceneManager = SceneManager::GetInstace();
	sceneManager.Finalize();
}
