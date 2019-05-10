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
	//�@���W�̍X�V
	m_worldVel += m_worldAccel;
	m_worldPos += m_worldVel;

	// �}�g���N�X���X�V
	m_worldMatrix = Matrix::CreateFromQuaternion(m_worldDir) * Matrix::CreateTranslation(m_worldPos);


	// �q���̃}�g���N�X���X�V
	UpdateChildMatrix(elapsedTime);
}

/// <summary>
/// �q���̃}�g���N�X���X�V����
/// </summary>
/// <param name="elapsedTime"></param>
void Transform::UpdateChildMatrix(float elapsedTime)
{
	for (auto ite = m_childList.begin(); ite != m_childList.end(); ite++)
	{
		// ���W���X�V
		Vector3 pos = (*ite)->WorldPos() + m_worldVel;
		(*ite)->WorldPos(pos);
		// �}�g���N�X���X�V
		Matrix matrix = Matrix::CreateFromQuaternion((*ite)->WorldDir()) * Matrix::CreateTranslation((*ite)->WorldPos());
		(*ite)->WorldMatrix(matrix);
	}
}

/// <summary>
/// �q���̍��W�̍X�V
/// </summary>
/// <param name="pos"></param>
void Transform::UpdateChildPos(DirectX::SimpleMath::Vector3 & pos)
{
	for (auto ite = m_childList.begin(); ite != m_childList.end(); ite++)
	{
		// ���W���X�V
		(*ite)->WorldPos((*ite)->WorldPos() + pos);
		(*ite)->UpdateChildPos(pos);
	}
}

/// <summary>
/// �q���̌����̍X�V
/// </summary>
/// <param name="dir"></param>
void Transform::UpdateChildDir(DirectX::SimpleMath::Quaternion & dir)
{
	for (auto ite = m_childList.begin(); ite != m_childList.end(); ite++)
	{
		// �������X�V
		(*ite)->WorldDir((*ite)->WorldDir() * dir);
		(*ite)->UpdateChildDir(dir);
	}
}

/// <summary>
/// ���[���h�̌�����ݒ肷��
/// </summary>
/// <param name="dir"></param>
void Transform::WorldDir(DirectX::SimpleMath::Quaternion & dir)
{
	Vector3 from = Vector3::Transform(Vector3::Forward, m_worldDir);
	Vector3 to = Vector3::Transform(Vector3::Forward, dir);
	Quaternion q = FromToRotation(from, to);
	UpdateChildDir(q);
	m_worldDir = dir;
}

/// <summary>
/// ���[�J���̍��W���擾����(�e�̍��W�����_�Ƃ������W���擾)
/// </summary>
/// <returns></returns>
DirectX::SimpleMath::Vector3 Transform::LocalPos()
{
	if (m_parent) 
	{ 
		return m_worldPos - m_parent->WorldPos();
	}
	return m_worldPos;
}

/// <summary>
/// ���[�J���̍��W��ݒ肷��
/// </summary>
/// <param name="pos"></param>
void Transform::LocalPos(DirectX::SimpleMath::Vector3 & localPos)
{
	if (m_parent) 
	{ 
		m_worldPos = m_parent->WorldPos() + localPos;
	}
	else 
	{ 
		m_worldPos = localPos;
	}
}

/// <summary>
/// ���[�J�����W�̑��x���擾����
/// </summary>
/// <returns></returns>
DirectX::SimpleMath::Vector3 Transform::LocalVel()
{
	Quaternion inv = Quaternion::Identity;
	m_worldDir.Inverse(inv);
	return Vector3::Transform(m_worldVel, inv);
}

/// <summary>
/// ���[�J�����W�̑��x��ݒ肷��
/// </summary>
/// <returns></returns>
void Transform::LocalVel(DirectX::SimpleMath::Vector3 & localVel)
{
	m_worldVel = Vector3::Transform(localVel, m_worldDir);
}

/// <summary>
/// ���[�J�����W�̉����x���擾����
/// </summary>
/// <returns></returns>
DirectX::SimpleMath::Vector3 Transform::LocalAccel()
{
	Quaternion inv = Quaternion::Identity;
	m_worldDir.Inverse(inv);
	return Vector3::Transform(m_worldAccel, inv);
}

/// <summary>
/// ���[�J�����W�̉����x��ݒ肷��
/// </summary>
/// <returns></returns>
void Transform::LocalAccel(DirectX::SimpleMath::Vector3 & localAccel)
{
	m_worldAccel = Vector3::Transform(localAccel, m_worldDir);
}

/// <summary>
/// ���[�J�����W�̌������擾����
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
/// ���[�J���̌�����ݒ肷��
/// </summary>
/// <param name="dir"></param>
void Transform::LocalDir(DirectX::SimpleMath::Quaternion & localDir)
{
	Quaternion q = Quaternion::Identity;
	Vector3 from = Vector3::Transform(Vector3::Forward, m_worldDir);
	Vector3 to = Vector3::Zero;

	// ���g�̌����̍X�V
	if (m_parent)
	{
		to = Vector3::Transform(Vector3::Forward, m_parent->WorldDir() * localDir);
		m_worldDir = m_parent->WorldDir() * localDir;
	}
	else
	{
		to = Vector3::Transform(Vector3::Forward, localDir);
		m_worldDir = localDir;
	}

	// �q���̌����̍X�V
	q = FromToRotation(from, to);
	UpdateChildDir(q);
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

/// <summary>
/// from ���� to �܂ł̉�]���v�Z����
/// </summary>
DirectX::SimpleMath::Quaternion Transform::FromToRotation(DirectX::SimpleMath::Vector3& fromNormalize, DirectX::SimpleMath::Vector3& toNormalize)
{
	// �p�x�����߂�
	float cosine = fromNormalize.Dot(toNormalize);
	if (cosine > 1.0f) cosine = 1.0f;
	else if (cosine < -1.0f) cosine = -1.0f;

	float angle = acos(cosine);

	// �������߂�
	Vector3 axis = fromNormalize.Cross(toNormalize);
	if (axis == Vector3::Zero)
	{

		// fromNormalize �� toNormalize ���������^���΂̏ꍇ
		// Vector3::Forward �� fromNormalize �Ō��݂̉�]�����߂�
		float cosineOrigin = Vector3::Forward.Dot(fromNormalize);
		if (cosineOrigin > 1.0f) cosineOrigin = 1.0f;
		else if (cosineOrigin < -1.0f) cosineOrigin = -1.0f;
		float angleOrigin = acos(cosineOrigin);

		Vector3 axisOrigin = Vector3::Forward.Cross(fromNormalize);

		if (axisOrigin == Vector3::Zero)
		{
			// Vector3::Forward �� fromNormalize ���������^���΂̏ꍇ
			// Quaternion::Identity �� 180�x��]������
			if (cosineOrigin == -1.0f)
			{
				return Quaternion::CreateFromAxisAngle(Vector3::Up, XMConvertToRadians(180.0f));
			}
			else
			{
				return Quaternion::Identity;
			}
		}


		// ���݂̉�]����N�H�[�^�j�I�������߂�
		Quaternion qOrigin = Quaternion::CreateFromAxisAngle(axisOrigin, angleOrigin);

		if (cosine == -1.0f)
		{
			// 180�x��]������
			axis = fromNormalize.Cross(Vector3::Transform(Vector3::Right, qOrigin));
			return Quaternion::CreateFromAxisAngle(axis, XMConvertToRadians(180.0f));
		}
		else
		{
			// ���݂̉�]�̃N�H�[�^�j�I����Ԃ�
			return qOrigin;
		}
	}

	Quaternion q = Quaternion::CreateFromAxisAngle(axis, angle);

	return q;
}