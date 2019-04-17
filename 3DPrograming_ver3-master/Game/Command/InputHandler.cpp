#include "../../pch.h"
#include "InputHandler.h"
#include "../Utility/InputManager.h"
#include "Accel.h"

using namespace std;
using namespace DirectX;

InputHandler::InputHandler()
{
	m_keyUpArrow = new Accel();
}

InputHandler::~InputHandler()
{
	delete m_keyUpArrow;
}

vector<Command*> InputHandler::GetInputHnadle()
{
	vector<Command*> commandList;

	InputManager& inputManager = InputManager::GetInstace();

	Keyboard::State key = inputManager.GetKeyboard();
	Keyboard::KeyboardStateTracker keyST = inputManager.GetKeyboardTracker();
	
	if (key.W)
	{
		commandList.push_back(m_keyUpArrow);
	}


	return commandList;
}
