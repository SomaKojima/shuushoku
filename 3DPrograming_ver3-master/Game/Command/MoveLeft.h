#pragma once

#include "Command.h"

/// <summary>
/// ���ړ��R�}���h�̃N���X
/// </summary>
class MoveLeft : public Command
{
public:
	// �R���X�g���N�^
	MoveLeft();
	// �f�X�g���N�^
	~MoveLeft();

public:
	// ���s�֐�
	void Excute(GameObject& obj) override;
};

