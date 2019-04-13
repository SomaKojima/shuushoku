#include "../../pch.h"
#include "Transform.h"

using namespace std;
using namespace DirectX;
using namespace DirectX::SimpleMath;

/// <summary>
/// �R���X�g���N�^
/// </summary>
Transform::Transform()
	:
	m_worldPos(DirectX::SimpleMath::Vector3::Zero),
	m_worldVel(DirectX::SimpleMath::Vector3::Zero),
	m_worldAccel(DirectX::SimpleMath::Vector3::Zero),
	m_worldDir(DirectX::SimpleMath::Quaternion::Identity),
	m_worldMatrix(DirectX::SimpleMath::Matrix::Identity),
	m_collisionSize(3),
	m_parent(nullptr)
{
}

/// <summary>
/// ����������
/// </summary>
void Transform::Initialize()
{
	// �����ړ�
	m_worldMatrix = Matrix::CreateFromQuaternion(m_worldDir) * Matrix::CreateTranslation(m_worldPos);
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="elapsedTime"></param>
void Transform::Update(float elapsedTime)
{
	// �}�g���N�X/���W�̍X�V
	m_worldVel += m_worldAccel;

	m_localPos += m_worldVel;

	m_localMatrix = Matrix::CreateFromQuaternion(m_localDir) * Matrix::CreateTranslation(m_localPos);
}

/// <summary>
/// ���[�J�����W���擾����
/// </summary>
/// <returns>�e����Ƀ��[�J�����W���擾����F�@�e�����Ȃ��ꍇ�̓��[���h���W��Ԃ�</returns>
DirectX::SimpleMath::Vector3 Transform::GetWorldToLocal(DirectX::SimpleMath::Vector3 world, DirectX::SimpleMath::Vector3 parentWorld)
{
	if (m_parent)
	{
		// �t��]���擾
		Quaternion inv = Quaternion::Identity;
		m_parent->WorldDir().Inverse(inv);
		// ���W���v�Z
		Vector3 vel = world - parentWorld;
		return Vector3::Transform(vel, inv);
	}
	// �e�����Ȃ��ꍇ
	return world;
}

/// <summary>
/// ���[�J�����W���擾����
/// </summary>
/// <returns></returns>
DirectX::SimpleMath::Vector3 Transform::SetLocalToWorld(DirectX::SimpleMath::Vector3 & local)
{
	if (m_parent)return m_parent->WorldVel() + Vector3::Transform(local, LocalDir());
	return Vector3::Transform(local, LocalDir());
}


/// <summary>
/// ���[�J�����W�̌���
/// </summary>
/// <returns></returns>
DirectX::SimpleMath::Quaternion Transform::LocalDir()
{
	if (m_parent)
	{
		// �e�̋t��]��������(���݂̌����@�[�@�e�̌���)
		Quaternion inv = Quaternion::Identity;
		m_parent->WorldDir().Inverse(inv);
		return m_worldDir * inv;
	}
	// �e�����Ȃ���Ύ��g�̉�]��Ԃ�
	return m_worldDir;
}

/// <summary>
/// ���[�J�����W�̃}�g���N�X
/// </summary>
/// <returns></returns>
DirectX::SimpleMath::Matrix Transform::LocalMatrix()
{
	if (m_parent)
	{
		return Matrix::CreateFromQuaternion(LocalDir()) * Matrix::CreateTranslation(LocalPos());
	}
	return m_worldMatrix;
}
