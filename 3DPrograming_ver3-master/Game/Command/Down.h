#pragma once

#include "Command.h"

/// <summary>
/// ���~�R�}���h�̃N���X
/// </summary>
class Down : public Command
{
public:
	// �R���X�g���N�^
	Down();
	~Down();

public:
	// ���s�֐�
	void Excute(GameObject& obj) override;
};
