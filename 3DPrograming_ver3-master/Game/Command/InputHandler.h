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
	// W�L�[�̃R�}���h
	Command* m_keyW;
	// A�L�[�̃R�}���h
	Command* m_keyA;
	// S�L�[�̃R�}���h
	Command* m_keyS;
	// D�L�[�̃R�}���h
	Command* m_keyD;

	// Z�L�[�̃R�}���h
	Command* m_keyZ;
	// X�L�[�̃R�}���h
	Command* m_keyX;

	// �X�y�[�X�L�[�̃R�}���h
	Command* m_keySpace;

	// ���̓n���h�����擾
	std::vector<Command*> GetInputHnadle();

private:
};