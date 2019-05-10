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
/// ローカル座標の速度を取得する
/// </summary>
/// <returns></returns>
DirectX::SimpleMath::Vector3 Transform::LocalVel()
{
	Quaternion inv = Quaternion::Identity;
	m_worldDir.Inverse(inv);
	return Vector3::Transform(m_worldVel, inv);
}

/// <summary>
/// ローカル座標の速度を設定する
/// </summary>
/// <returns></returns>
void Transform::LocalVel(DirectX::SimpleMath::Vector3 & localVel)
{
	m_worldVel = Vector3::Transform(localVel, m_worldDir);
}

/// <summary>
/// ローカル座標の加速度を取得する
/// </summary>
/// <returns></returns>
DirectX::SimpleMath::Vector3 Transform::LocalAccel()
{
	Quaternion inv = Quaternion::Identity;
	m_worldDir.Inverse(inv);
	return Vector3::Transform(m_worldAccel, inv);
}

/// <summary>
/// ローカル座標の加速度を設定する
/// </summary>
/// <returns></returns>
void Transform::LocalAccel(DirectX::SimpleMath::Vector3 & localAccel)
{
	m_worldAccel = Vector3::Transform(localAccel, m_worldDir);
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
void Transform::LocalDir(DirectX::SimpleMath::Quaternion & localDir)
{
	Quaternion q = Quaternion::Identity;
	Vector3 from = Vector3::Transform(Vector3::Forward, m_worldDir);
	Vector3 to = Vector3::Zero;

	// 自身の向きの更新
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
	if (axis == Vector3::Zero)
	{

		// fromNormalize と toNormalize が同じか真反対の場合
		// Vector3::Forward と fromNormalize で現在の回転を求める
		float cosineOrigin = Vector3::Forward.Dot(fromNormalize);
		if (cosineOrigin > 1.0f) cosineOrigin = 1.0f;
		else if (cosineOrigin < -1.0f) cosineOrigin = -1.0f;
		float angleOrigin = acos(cosineOrigin);

		Vector3 axisOrigin = Vector3::Forward.Cross(fromNormalize);

		if (axisOrigin == Vector3::Zero)
		{
			// Vector3::Forward と fromNormalize が同じか真反対の場合
			// Quaternion::Identity か 180度回転させる
			if (cosineOrigin == -1.0f)
			{
				return Quaternion::CreateFromAxisAngle(Vector3::Up, XMConvertToRadians(180.0f));
			}
			else
			{
				return Quaternion::Identity;
			}
		}


		// 現在の回転からクォータニオンを求める
		Quaternion qOrigin = Quaternion::CreateFromAxisAngle(axisOrigin, angleOrigin);

		if (cosine == -1.0f)
		{
			// 180度回転させる
			axis = fromNormalize.Cross(Vector3::Transform(Vector3::Right, qOrigin));
			return Quaternion::CreateFromAxisAngle(axis, XMConvertToRadians(180.0f));
		}
		else
		{
			// 現在の回転のクォータニオンを返す
			return qOrigin;
		}
	}

	Quaternion q = Quaternion::CreateFromAxisAngle(axis, angle);

	return q;
}