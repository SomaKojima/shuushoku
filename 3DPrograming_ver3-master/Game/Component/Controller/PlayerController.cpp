#include "../../pch.h"
#include "PlayerController.h"
#include <vector>

using namespace std;

/// <summary>
/// �R���X�g���N�^
/// </summary>
PlayerController::PlayerController()
{
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
PlayerController::~PlayerController()
{
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="elapsedTime"></param>
void PlayerController::Update(float elapsedTime)
{
	 vector<Command*> commandVec = inputHnadler.GetInputHnadle();
	 for (auto ite = commandVec.begin(); ite != commandVec.end(); ite++)
	 {
		 (*ite)->Excute(*m_gameObject);
	 }
}
