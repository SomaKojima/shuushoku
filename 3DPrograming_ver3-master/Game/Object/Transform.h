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
	DirectX::SimpleMath::Vector3 WorldPos();
	// ���[���h���W�̑��x���擾����
	DirectX::SimpleMath::Vector3 WorldVel();
	// ���[���h���W�̉����x���擾����
	DirectX::SimpleMath::Vector3 WorldAccel();
	// ���[���h���W�̌������擾����
	DirectX::SimpleMath::Quaternion WorldDir();
	// ���[���h���W�̃}�g���N�X���擾����
	DirectX::SimpleMath::Matrix WorldMatrix();


	// ���[�J�����W���擾
	DirectX::SimpleMath::Vector3 LocalPos() { return m_localPos; }
	// ���[�J�����x���擾
	DirectX::SimpleMath::Vector3 LocalVel() { return m_localVel; }
	// ���[�J�������x���擾
	DirectX::SimpleMath::Vector3 LocalAccel() { return m_localAccel; }
	// ���[�J���������擾
	DirectX::SimpleMath::Quaternion LocalDir() { return m_localDir; }
	// ���[�J���}�g���N�X���擾
	DirectX::SimpleMath::Matrix LocalMatrix() { return m_localMatrix; }

	/// <summary>
	/// �q���̃��X�g�ɒǉ�����
	/// </summary>
	/// <param name="transform"></param>
	void AddChild(Transform* transform) { m_childList.push_back(transform); }

private:
	DirectX::SimpleMath::Vector3 m_localPos;		// ���W
	DirectX::SimpleMath::Vector3 m_localVel;		// ���x
	DirectX::SimpleMath::Vector3 m_localAccel;		// ���x
	DirectX::SimpleMath::Quaternion m_localDir;		// ����
	DirectX::SimpleMath::Matrix m_localMatrix;		// �}�g���N�X

private:						
	Transform* m_parent;					// �e�̏��
	std::list<Transform*> m_childList;		// �q���̃��X�g�̏��
};