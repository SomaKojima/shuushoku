#include "../../pch.h"
#include "PositionControl.h"

using namespace std;
using namespace DirectX;
using namespace DirectX::SimpleMath;

/// <summary>
/// コンストラクタ
/// </summary>
PositionControl::PositionControl()
	:
	m_isWallHit(false)
{
}

/// <summary>
/// デストラクタ
/// </summary>
PositionControl::~PositionControl()
{
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="elapsedTime"></param>
void PositionControl::Update(float elapsedTime)
{
	// 正規化する
	m_normal.Normalize();

	// 姿勢を合わせ
	Vector3 upDir = Vector3::Transform(Vector3::Up, m_gameObject->GetTransform().WorldDir());
	// 回転軸計算
	Vector3 axis = upDir.Cross(m_normal);
	if (axis != Vector3::Zero && m_normal != Vector3::Zero)
	{
		// 角度を求める
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
