#pragma once

#include "Command.h"

/// <summary>
/// �}�E�X�J�[�\����ύX����R�}���h�̃N���X
/// </summary>
class ChangeMouseCursor : public Command
{
public:
	// �R���X�g���N�^
	ChangeMouseCursor();
	~ChangeMouseCursor();

public:
	// ���s�֐�
	void Excute(GameObject& obj) override;

};