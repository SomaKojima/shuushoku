#pragma once

#include "../Component.h"

/// <summary>
/// ���C�̃R���|�[�l���g
/// </summary>
class Friction : public Component
{
public:
	// �R���X�g���N�^
	Friction();
	// �f�X�g���N�^
	~Friction();

public:
	// �x���X�V����
	void LateUpdate(float elapsedTime) override;

};