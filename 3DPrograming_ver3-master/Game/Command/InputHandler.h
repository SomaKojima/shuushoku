#pragma once

#include <vector>
#include "Command.h"


class InputHandler
{
public:
	// �R���X�g���N�^
	InputHandler();
	// �f�X�g���N�^
	~InputHandler();

public:
	// ��L�[�̃R�}���h
	Command* m_keyUpArrow;

	// ���̓n���h�����擾
	std::vector<Command*> GetInputHnadle();

private:
};