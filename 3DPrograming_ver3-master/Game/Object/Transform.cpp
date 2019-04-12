#include "../../pch.h"
#include "Transform.h"

using namespace std;
using namespace DirectX;
using namespace DirectX::SimpleMath;

/// <summary>
/// コンストラクタ
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
/// 初期化処理
/// </summary>
void Transform::Initialize()
{
	// 初期移動
	m_localMatrix = Matrix::CreateFromQuaternion(m_localDir) * Matrix::CreateTranslation(m_localPos);
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="elapsedTime"></param>
void Transform::Update(float elapsedTime)
{
	// マトリクス/座標の更新
	m_localVel += m_localAccel;

	m_localPos += m_localVel;

	m_localMatrix = Matrix::CreateFromQuaternion(m_localDir) * Matrix::CreateTranslation(m_localPos);
}

/// <summary>
/// ワールド座標を取得
/// </summary>
/// <returns></returns>
DirectX::SimpleMath::Vector3 Transform::WorldPos()
{
	if (!m_parent) return m_localPos;
	return WorldMatrix().Translation();
}

/// <summary>
/// ワールド座標を設定
/// </summary>
/// <param name="pos"></param>
void Transform::WorldPos(DirectX::SimpleMath::Vector3& pos)
{
	Vector3 _pos = pos - WorldPos();
	m_localPos = pos;
}

/// <summary>
/// ワールド座標の速度を取得
/// </summary>
/// <returns></returns>
DirectX::SimpleMath::Vector3 Transform::WorldVel()
{
	if (!m_parent) return Vector3::Transform(m_localVel, m_localDir);
	return m_parent->WorldVel() + Vector3::Transform(m_localVel, m_localDir);
}

/// <summary>
/// ワールド座標の速度を取得する
/// </summary>
/// <returns></returns>
DirectX::SimpleMath::Vector3 Transform::WorldAccel()
{
	if (!m_parent) return Vector3::Transform(m_localAccel, m_localDir);
	return m_parent->WorldAccel() + Vector3::Transform(m_localAccel, m_localDir);
}

/// <summary>
/// ワールド座標の向き
/// </summary>
/// <returns></returns>
DirectX::SimpleMath::Quaternion Transform::WorldDir()
{
	if (!m_parent) return m_localDir;
	return m_parent->WorldDir() * m_localDir;
}

/// <summary>
/// ワールド座標のマトリクス
/// </summary>
/// <returns></returns>
DirectX::SimpleMath::Matrix Transform::WorldMatrix()
{
	if (!m_parent) return m_localMatrix;
	return m_parent->WorldMatrix() * m_localMatrix;
}
