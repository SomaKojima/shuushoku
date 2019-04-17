#include "../../pch.h"
#include "PlayerController.h"
#include <vector>

using namespace std;

/// <summary>
/// コンストラクタ
/// </summary>
PlayerController::PlayerController()
{
}

/// <summary>
/// デストラクタ
/// </summary>
PlayerController::~PlayerController()
{
}

/// <summary>
/// 更新処理
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
