#pragma once

#include <list>

/// <summary>
/// �ό`�̃N���X
/// </summary>
class Transform
{
public:
	// �R���X�g���N�^
	Transform();

public:
	// ����������
	void Initialize();
	// �X�V����
	void Update(float elapsedTime);



	// ���[���h���W���擾����
	DirectX::SimpleMath::Vector3 LocalPos() { return GetWorldToLocal(m_worldPos, m_parent->WorldPos()); }
	void LocalPos(DirectX::SimpleMath::Vector3& pos) { m_worldPos = SetLocalToWorld(pos); }

	// ���[���h���W�̑��x���擾����
	DirectX::SimpleMath::Vector3 LocalVel() { return GetWorldToLocal(m_worldVel , m_parent->WorldVel()); }
	void LocalVel(DirectX::SimpleMath::Vector3& vel) { m_worldVel = SetLocalToWorld(vel); }

	// ���[���h���W�̉����x���擾����
	DirectX::SimpleMath::Vector3 LocalAccel() { return GetWorldToLocal(m_worldAccel, m_parent->WorldAccel()); }
	void LocalAccel(DirectX::SimpleMath::Vector3 accel) { m_worldAccel = SetLocalToWorld(accel); }

	// ���[���h���W�̌������擾����
	DirectX::SimpleMath::Quaternion LocalDir();

	// ���[���h���W�̃}�g���N�X���擾����
	DirectX::SimpleMath::Matrix LocalMatrix();



	// ���[���h���W�����W���擾
	DirectX::SimpleMath::Vector3 WorldPos() { return m_worldPos; }
	void WorldPos(DirectX::SimpleMath::Vector3& pos) { m_worldPos = pos; }

	// ���[���h���x���擾
	DirectX::SimpleMath::Vector3 WorldVel() { return m_worldVel; }
	void WorldVel(DirectX::SimpleMath::Vector3& vel) { m_worldVel = vel; }

	// ���[���h�����x���擾
	DirectX::SimpleMath::Vector3 WorldAccel() { return m_worldAccel; }
	void WorldAccel(DirectX::SimpleMath::Vector3& accel) { m_worldAccel = accel; }

	// ���[���h�������擾
	DirectX::SimpleMath::Quaternion WorldDir() { return m_worldDir; }
	void WorldDir(DirectX::SimpleMath::Quaternion& dir) { m_worldDir = dir; }

	// ���[���h�}�g���N�X�擾
	DirectX::SimpleMath::Matrix WorldMatrix() { return m_worldMatrix; }
	void WorldMatrix(DirectX::SimpleMath::Matrix& matrix) { m_worldMatrix = matrix; }

	// �傫�����擾
	float CollisionSize() { return m_collisionSize; }
	void CollisionSize(float size) { m_collisionSize = size; }

	/// <summary>
	/// �q���̃��X�g�ɒǉ�����
	/// </summary>
	/// <param name="transform"></param>
	void AddChild(Transform* transform) { m_childList.push_back(transform); }

private:
	// ���W�E���x�E�����x�̃��[�J�����W�̎擾�̌v�Z
	DirectX::SimpleMath::Vector3 GetWorldToLocal(DirectX::SimpleMath::Vector3 world, DirectX::SimpleMath::Vector3 parentWorld);
	// ���W�E���x�E�����x�̃��[�J�����W�̐ݒ�̌v�Z
	DirectX::SimpleMath::Vector3 SetLocalToWorld(DirectX::SimpleMath::Vector3& local);

private:
	DirectX::SimpleMath::Vector3 m_worldPos;		// ���W

	DirectX::SimpleMath::Vector3 m_worldVel;		// ���x
	DirectX::SimpleMath::Vector3 m_worldAccel;		// �����x
	DirectX::SimpleMath::Quaternion m_worldDir;		// ����
	DirectX::SimpleMath::Matrix m_worldMatrix;		// �}�g���N�X
	float m_collisionSize;

private:						
	Transform* m_parent;					// �e�̏��
	std::list<Transform*> m_childList;		// �q���̃��X�g�̏��
};