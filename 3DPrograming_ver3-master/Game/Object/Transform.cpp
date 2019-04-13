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
/// 初期化処理
/// </summary>
void Transform::Initialize()
{
	// 初期移動
	m_worldMatrix = Matrix::CreateFromQuaternion(m_worldDir) * Matrix::CreateTranslation(m_worldPos);
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="elapsedTime"></param>
void Transform::Update(float elapsedTime)
{
	// マトリクス/座標の更新
	m_worldVel += m_worldAccel;

	m_localPos += m_worldVel;

	m_localMatrix = Matrix::CreateFromQuaternion(m_localDir) * Matrix::CreateTranslation(m_localPos);
}

/// <summary>
/// ローカル座標を取得する
/// </summary>
/// <returns>親を基準にローカル座標を取得する：　親がいない場合はワールド座標を返す</returns>
DirectX::SimpleMath::Vector3 Transform::GetWorldToLocal(DirectX::SimpleMath::Vector3 world, DirectX::SimpleMath::Vector3 parentWorld)
{
	if (m_parent)
	{
		// 逆回転を取得
		Quaternion inv = Quaternion::Identity;
		m_parent->WorldDir().Inverse(inv);
		// 座標を計算
		Vector3 vel = world - parentWorld;
		return Vector3::Transform(vel, inv);
	}
	// 親がいない場合
	return world;
}

/// <summary>
/// ローカル座標を取得する
/// </summary>
/// <returns></returns>
DirectX::SimpleMath::Vector3 Transform::SetLocalToWorld(DirectX::SimpleMath::Vector3 & local)
{
	if (m_parent)return m_parent->WorldVel() + Vector3::Transform(local, LocalDir());
	return Vector3::Transform(local, LocalDir());
}


/// <summary>
/// ローカル座標の向き
/// </summary>
/// <returns></returns>
DirectX::SimpleMath::Quaternion Transform::LocalDir()
{
	if (m_parent)
	{
		// 親の逆回転を加える(現在の向き　ー　親の向き)
		Quaternion inv = Quaternion::Identity;
		m_parent->WorldDir().Inverse(inv);
		return m_worldDir * inv;
	}
	// 親がいなければ自身の回転を返す
	return m_worldDir;
}

/// <summary>
/// ローカル座標のマトリクス
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
