#include "../../pch.h"
#include "PositionControl.h"

using namespace std;
using namespace DirectX;
using namespace DirectX::SimpleMath;

/// <summary>
/// �R���X�g���N�^
/// </summary>
PositionControl::PositionControl()
	:
	m_isWallHit(false)
{
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
PositionControl::~PositionControl()
{
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="elapsedTime"></param>
void PositionControl::Update(float elapsedTime)
{
	// ���K������
	m_normal.Normalize();

	// �p�������킹
	Vector3 upDir = Vector3::Transform(Vector3::Up, m_gameObject->GetTransform().WorldDir());
	// ��]���v�Z
	Vector3 axis = upDir.Cross(m_normal);
	if (axis != Vector3::Zero && m_normal != Vector3::Zero)
	{
		// �p�x�����߂�
		float cosine = upDir.Dot(m_normal);
		if (cosine > 1.0f)
		{
			cosine = 1.0f;
		}
		float rot = acos(cosine);
		Quaternion  Q1 = Quaternion::CreateFromAxisAngle(axis, rot);
		Quaternion q = Quaternion::Slerp(m_gameObject->GetTransform().WorldDir(), m_gameObject->GetTransform().WorldDir() * Q1, 1.0f);

		m_gameObject->GetTransform().WorldDir(q);
	}

	m_isWallHit = false;
}

void PositionControl::OnTriangleCollision(GameObject & obj, const Collision::Triangle & triangle, DirectX::SimpleMath::Vector3 & hitPos)
{
	if (obj.GetName() == "Wall")
	{
		if (!m_isWallHit)
		{
			m_normal = Vector3::Zero;
		}
		m_isWallHit = true;
		m_normal += Vector3(triangle.plane.a, triangle.plane.b, triangle.plane.c);
	}
}
