#pragma once

#include "Command.h"

/// <summary>
/// �O�i�R�}���h�̃N���X
/// </summary>
class MoveForward : public Command
{
public:
	// �R���X�g���N�^
	MoveForward();
	~MoveForward();

public:
	// ���s�֐�
	void Excute(GameObject& obj) override;
};