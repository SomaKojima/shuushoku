#include "../../pch.h"
#include "InputHandler.h"
#include "../Utility/InputManager.h"

#include "Accel.h"
#include "Up.h"
#include "Down.h"
#include "ChangeMouseCursor.h"

using namespace std;
using namespace DirectX;

InputHandler::InputHandler()
{
	m_keyUpArrow = new Accel();
	m_keyZ = new Up();
	m_keyX = new Down();
	m_keySpace = new ChangeMouseCursor();
}

InputHandler::~InputHandler()
{
	delete m_keyUpArrow;
	delete m_keyZ;
	delete m_keyX;
	delete m_keySpace;
}

vector<Command*> InputHandler::GetInputHnadle()
{
	vector<Command*> commandList;

	InputManager& inputManager = InputManager::GetInstace();

	Keyboard::State key = inputManager.GetKeyboard();
	Keyboard::KeyboardStateTracker keyST = inputManager.GetKeyboardTracker();
	
	if (key.W) commandList.push_back(m_keyUpArrow);
	if (key.Q) commandList.push_back(m_keyZ);
	if (key.E) commandList.push_back(m_keyX);
	if (keyST.pressed.Space) commandList.push_back(m_keySpace);

	return commandList;
}
