#pragma once

#include <list>

/// <summary>
/// 変形のクラス
/// </summary>
class Transform
{
public:
	// コンストラクタ
	Transform();

public:
	// 初期化処理
	void Initialize();
	// 更新処理
	void Update(float elapsedTime);

	// ワールド座標を取得する
	DirectX::SimpleMath::Vector3 WorldPos();
	void WorldPos(DirectX::SimpleMath::Vector3& pos);

	// ワールド座標の速度を取得する
	DirectX::SimpleMath::Vector3 WorldVel();

	// ワールド座標の加速度を取得する
	DirectX::SimpleMath::Vector3 WorldAccel();

	// ワールド座標の向きを取得する
	DirectX::SimpleMath::Quaternion WorldDir();

	// ワールド座標のマトリクスを取得する
	DirectX::SimpleMath::Matrix WorldMatrix();


	// ローカル座標を取得
	DirectX::SimpleMath::Vector3 LocalPos() { return m_localPos; }
	void LocalPos(DirectX::SimpleMath::Vector3& pos) { m_localPos = pos; }

	// ローカル速度を取得
	DirectX::SimpleMath::Vector3 LocalVel() { return m_localVel; }
	void LocalVel(DirectX::SimpleMath::Vector3& vel) { m_localVel = vel; }

	// ローカル加速度を取得
	DirectX::SimpleMath::Vector3 LocalAccel() { return m_localAccel; }
	void LocalAccel(DirectX::SimpleMath::Vector3& accel) { m_localAccel = accel; }

	// ローカル向きを取得
	DirectX::SimpleMath::Quaternion LocalDir() { return m_localDir; }
	void LocalDir(DirectX::SimpleMath::Quaternion& dir) { m_localDir = dir; }

	// ローカルマトリクスを取得
	DirectX::SimpleMath::Matrix LocalMatrix() { return m_localMatrix; }
	void LocalMatrix(DirectX::SimpleMath::Matrix& matrix) { m_localMatrix = matrix; }

	// 大きさを取得
	float CollisionSize() { return m_collisionSize; }

	/// <summary>
	/// 子供のリストに追加する
	/// </summary>
	/// <param name="transform"></param>
	void AddChild(Transform* transform) { m_childList.push_back(transform); }

private:
	DirectX::SimpleMath::Vector3 m_localPos;		// 座標
	DirectX::SimpleMath::Vector3 m_localVel;		// 速度
	DirectX::SimpleMath::Vector3 m_localAccel;		// 速度
	DirectX::SimpleMath::Quaternion m_localDir;		// 向き
	DirectX::SimpleMath::Matrix m_localMatrix;		// マトリクス
	float m_collisionSize;

private:						
	Transform* m_parent;					// 親の情報
	std::list<Transform*> m_childList;		// 子供のリストの情報
};