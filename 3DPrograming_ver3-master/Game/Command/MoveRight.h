#pragma once

#include "Command.h"

/// <summary>
/// �E�ړ��R�}���h�̃N���X
/// </summary>
class MoveRight : public Command
{
public:
	// �R���X�g���N�^
	MoveRight();
	// �f�X�g���N�^
	~MoveRight();

public:
	// ���s�֐�
	void Excute(GameObject& obj) override;
};