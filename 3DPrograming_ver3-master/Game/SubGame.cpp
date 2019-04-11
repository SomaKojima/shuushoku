#include "../pch.h"
#include "SubGame.h"
#include "../Game.h"

#include "Utility/InputManager.h"
#include "Scene/SceneManager.h"

SubGame::SubGame()
	:
	m_game(nullptr)
{
}

SubGame::~SubGame()
{
	m_game = nullptr;
}

void SubGame::Initialize(Game* game)
{
	m_game = game;
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
	sceneManager.Update(elapsedTime);
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
