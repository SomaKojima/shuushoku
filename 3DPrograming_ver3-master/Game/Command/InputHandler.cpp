#include "../../pch.h"
#include "InputHandler.h"
#include "../Utility/InputManager.h"

#include "MoveForward.h"
#include "MoveRight.h"
#include "MoveLeft.h"
#include "MoveBackward.h"

#include "Up.h"
#include "Down.h"
#include "ChangeMouseCursor.h"

using namespace std;
using namespace DirectX;

/// <summary>
/// コンストラクタ
/// </summary>
InputHandler::InputHandler()
{
	m_keyW = new MoveForward();
	m_keyA = new MoveLeft();
	m_keyS = new MoveBackward();
	m_keyD = new MoveRight();

	m_keyZ = new Up();
	m_keyX = new Down();
	m_keySpace = new ChangeMouseCursor();
}

/// <summary>
/// デストラクタ
/// </summary>
InputHandler::~InputHandler()
{
	delete m_keyW;
	delete m_keyA;
	delete m_keyS;
	delete m_keyD;

	delete m_keyZ;
	delete m_keyX;
	delete m_keySpace;
}

/// <summary>
/// 入力ハンドルを取得
/// </summary>
/// <returns></returns>
vector<Command*> InputHandler::GetInputHnadle()
{
	vector<Command*> commandList;

	InputManager& inputManager = InputManager::GetInstace();

	Keyboard::State key = inputManager.GetKeyboard();
	Keyboard::KeyboardStateTracker keyST = inputManager.GetKeyboardTracker();
	
	if (key.W) commandList.push_back(m_keyW);
	if (key.A) commandList.push_back(m_keyA);
	if (key.S) commandList.push_back(m_keyS);
	if (key.D) commandList.push_back(m_keyD);

	if (key.Q) commandList.push_back(m_keyZ);
	if (key.E) commandList.push_back(m_keyX);
	if (keyST.pressed.Space) commandList.push_back(m_keySpace);

	return commandList;
}
