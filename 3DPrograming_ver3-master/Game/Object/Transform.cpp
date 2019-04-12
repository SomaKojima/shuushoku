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
	m_localPos(DirectX::SimpleMath::Vector3::Zero),
	m_localVel(DirectX::SimpleMath::Vector3::Zero),
	m_localAccel(DirectX::SimpleMath::Vector3::Zero),
	m_localDir(DirectX::SimpleMath::Quaternion::Identity),
	m_localMatrix(DirectX::SimpleMath::Matrix::Identity),
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
	m_localMatrix = Matrix::CreateFromQuaternion(m_localDir) * Matrix::CreateTranslation(m_localPos);
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="elapsedTime"></param>
void Transform::Update(float elapsedTime)
{
	// �}�g���N�X/���W�̍X�V
	m_localVel += m_localAccel;

	m_localPos += m_localVel;

	m_localMatrix = Matrix::CreateFromQuaternion(m_localDir) * Matrix::CreateTranslation(m_localPos);
}

/// <summary>
/// ���[���h���W���擾
/// </summary>
/// <returns></returns>
DirectX::SimpleMath::Vector3 Transform::WorldPos()
{
	if (!m_parent) return m_localPos;
	return WorldMatrix().Translation();
}

/// <summary>
/// ���[���h���W��ݒ�
/// </summary>
/// <param name="pos"></param>
void Transform::WorldPos(DirectX::SimpleMath::Vector3& pos)
{
	Vector3 _pos = pos - WorldPos();
	m_localPos = pos;
}

/// <summary>
/// ���[���h���W�̑��x���擾
/// </summary>
/// <returns></returns>
DirectX::SimpleMath::Vector3 Transform::WorldVel()
{
	if (!m_parent) return Vector3::Transform(m_localVel, m_localDir);
	return m_parent->WorldVel() + Vector3::Transform(m_localVel, m_localDir);
}

/// <summary>
/// ���[���h���W�̑��x���擾����
/// </summary>
/// <returns></returns>
DirectX::SimpleMath::Vector3 Transform::WorldAccel()
{
	if (!m_parent) return Vector3::Transform(m_localAccel, m_localDir);
	return m_parent->WorldAccel() + Vector3::Transform(m_localAccel, m_localDir);
}

/// <summary>
/// ���[���h���W�̌���
/// </summary>
/// <returns></returns>
DirectX::SimpleMath::Quaternion Transform::WorldDir()
{
	if (!m_parent) return m_localDir;
	return m_parent->WorldDir() * m_localDir;
}

/// <summary>
/// ���[���h���W�̃}�g���N�X
/// </summary>
/// <returns></returns>
DirectX::SimpleMath::Matrix Transform::WorldMatrix()
{
	if (!m_parent) return m_localMatrix;
	return m_parent->WorldMatrix() * m_localMatrix;
}
