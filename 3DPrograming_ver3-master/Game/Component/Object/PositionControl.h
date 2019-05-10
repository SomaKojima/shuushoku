#pragma once

#include "../Component.h"

/// <summary>
/// ���C�̃R���|�[�l���g
/// </summary>
class PositionControl : public Component
{
public:
	// �R���X�g���N�^
	PositionControl();
	// �f�X�g���N�^
	~PositionControl();

public:
	// �X�V����
	void Update(float elapsedTime) override;
	
	// �ʂƂ̓����蔻��
	void OnTriangleCollision(GameObject& obj, const Collision::Triangle& triangle, DirectX::SimpleMath::Vector3& hitPos);

private:
	DirectX::SimpleMath::Vector3 m_normal;
	bool m_isWallHit;
};