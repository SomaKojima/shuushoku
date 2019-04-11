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

	/// <summary>
	/// ���[���h���W���擾����
	/// </summary>
	/// <returns></returns>
	DirectX::SimpleMath::Vector3 WorldPos();
	/// <summary>
	/// ���[���h���W�̑��x���擾����
	/// </summary>
	/// <returns></returns>
	DirectX::SimpleMath::Vector3 WorldVel();
	/// <summary>
	/// ���[���h���W�̉����x���擾����
	/// </summary>
	/// <returns></returns>
	DirectX::SimpleMath::Vector3 WorldAccel();
	/// <summary>
	/// ���[���h���W�̌������擾����
	/// </summary>
	/// <returns></returns>
	DirectX::SimpleMath::Quaternion WorldDir();
	/// <summary>
	/// ���[���h���W�̃}�g���N�X���擾����
	/// </summary>
	/// <returns></returns>
	DirectX::SimpleMath::Matrix WorldMatrix();

	/// <summary>
	/// �q���̃��X�g�ɒǉ�����
	/// </summary>
	/// <param name="transform"></param>
	void AddChild(Transform* transform) { m_childList.push_back(transform); }

public:
	DirectX::SimpleMath::Vector3 m_localPos;		// ���W
	DirectX::SimpleMath::Vector3 m_localVel;		// ���x
	DirectX::SimpleMath::Vector3 m_localAccel;		// ���x
	DirectX::SimpleMath::Quaternion m_localDir;		// ����
	DirectX::SimpleMath::Matrix m_localMatrix;		// ���[���h���W

private:						
	Transform* m_parent;					// �e�̏��
	std::list<Transform*> m_childList;		// �q���̃��X�g�̏��
};