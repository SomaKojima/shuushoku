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
}

void SubGame::Update(float elapsedTime)
{
	InputManager& inputManager = InputManager::GetInstace();
	inputManager.Update(elapsedTime);
}

void SubGame::Renderer()
{
}

void SubGame::Finalize()
{
}
