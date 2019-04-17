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
	//　座標の更新
	m_worldVel += m_worldAccel;
	m_worldPos += m_worldVel;

	// マトリクスを更新
	m_worldMatrix = Matrix::CreateFromQuaternion(m_worldDir) * Matrix::CreateTranslation(m_worldPos);

	// 子供のマトリクスを更新
	UpdateChildMatrix(elapsedTime);
}

/// <summary>
/// 子供のマトリクスを更新する
/// </summary>
/// <param name="elapsedTime"></param>
void Transform::UpdateChildMatrix(float elapsedTime)
{
	for (auto ite = m_childList.begin(); ite != m_childList.end(); ite++)
	{
		// 座標を更新
		Vector3 pos = (*ite)->WorldPos() + m_worldVel;
		(*ite)->WorldPos(pos);
		// マトリクスを更新
		Matrix matrix = Matrix::CreateFromQuaternion((*ite)->WorldDir()) * Matrix::CreateTranslation((*ite)->WorldPos());
		(*ite)->WorldMatrix(matrix);
	}
}

/// <summary>
/// 子供の座標の更新
/// </summary>
/// <param name="pos"></param>
void Transform::UpdateChildPos(DirectX::SimpleMath::Vector3 & pos)
{
	for (auto ite = m_childList.begin(); ite != m_childList.end(); ite++)
	{
		// 座標を更新
		(*ite)->WorldPos((*ite)->WorldPos() + pos);
		(*ite)->UpdateChildPos(pos);
	}
}

/// <summary>
/// 子供の向きの更新
/// </summary>
/// <param name="dir"></param>
void Transform::UpdateChildDir(DirectX::SimpleMath::Quaternion & dir)
{
	for (auto ite = m_childList.begin(); ite != m_childList.end(); ite++)
	{
		// 向きを更新
		(*ite)->WorldDir((*ite)->WorldDir() * dir);
		(*ite)->UpdateChildDir(dir);
	}
}

/// <summary>
/// ワールドの向きを設定する
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
/// ローカルの座標を取得する(親の座標を原点とした座標を取得)
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
/// ローカルの座標を設定する
/// </summary>
/// <param name="pos"></param>
void Transform::LocalPos(DirectX::SimpleMath::Vector3 & pos)
{
	if (m_parent) 
	{ 
		m_worldPos = m_parent->WorldPos() + pos;
	}
	else 
	{ 
		m_worldPos = pos;
	}
}

/// <summary>
/// ローカル座標の向きを取得する
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
/// ローカルの向きを設定する
/// </summary>
/// <param name="dir"></param>
void Transform::LocalDir(DirectX::SimpleMath::Quaternion & dir)
{
	Quaternion q = Quaternion::Identity;
	Vector3 from = Vector3::Transform(Vector3::Forward, m_worldDir);
	Vector3 to = Vector3::Zero;

	// 自身の向きの更新
	if (m_parent)
	{
		to = Vector3::Transform(Vector3::Forward, m_parent->WorldDir() * dir);
		m_worldDir = m_parent->WorldDir() * dir;
	}
	else
	{
		to = Vector3::Transform(Vector3::Forward, dir);
		m_worldDir = dir;
	}

	// 子供の向きの更新
	q = FromToRotation(from, to);
	UpdateChildDir(q);
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

/// <summary>
/// from から to までの回転を計算する
/// </summary>
DirectX::SimpleMath::Quaternion Transform::FromToRotation(DirectX::SimpleMath::Vector3& fromNormalize, DirectX::SimpleMath::Vector3& toNormalize)
{
	// 角度を求める
	float cosine = fromNormalize.Dot(toNormalize);
	if (cosine > 1.0f) cosine = 1.0f;
	else if (cosine < -1.0f) cosine = -1.0f;
	float angle = acos(cosine);

	// 軸を求める
	Vector3 axis = fromNormalize.Cross(toNormalize);

	return Quaternion::CreateFromAxisAngle(axis, angle);
}