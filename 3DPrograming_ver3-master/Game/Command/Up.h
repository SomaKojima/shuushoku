#pragma once

#include "Command.h"

/// <summary>
/// �㏸�R�}���h�̃N���X
/// </summary>
class Up : public Command
{
public:
	// �R���X�g���N�^
	Up();
	~Up();

public:
	// ���s�֐�
	void Excute(GameObject& obj) override;
};