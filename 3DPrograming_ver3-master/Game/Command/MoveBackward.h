#pragma once

#include "Command.h"

/// <summary>
/// ��ރR�}���h�̃N���X
/// </summary>
class MoveBackward : public Command
{
public:
	// �R���X�g���N�^
	MoveBackward();
	// �f�X�g���N�^
	~MoveBackward();

public:
	// ���s�֐�
	void Excute(GameObject& obj) override;
};
