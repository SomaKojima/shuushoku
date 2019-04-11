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

	/// <summary>
	/// ワールド座標を取得する
	/// </summary>
	/// <returns></returns>
	DirectX::SimpleMath::Vector3 WorldPos();
	/// <summary>
	/// ワールド座標の速度を取得する
	/// </summary>
	/// <returns></returns>
	DirectX::SimpleMath::Vector3 WorldVel();
	/// <summary>
	/// ワールド座標の加速度を取得する
	/// </summary>
	/// <returns></returns>
	DirectX::SimpleMath::Vector3 WorldAccel();
	/// <summary>
	/// ワールド座標の向きを取得する
	/// </summary>
	/// <returns></returns>
	DirectX::SimpleMath::Quaternion WorldDir();
	/// <summary>
	/// ワールド座標のマトリクスを取得する
	/// </summary>
	/// <returns></returns>
	DirectX::SimpleMath::Matrix WorldMatrix();

	/// <summary>
	/// 子供のリストに追加する
	/// </summary>
	/// <param name="transform"></param>
	void AddChild(Transform* transform) { m_childList.push_back(transform); }

public:
	DirectX::SimpleMath::Vector3 m_localPos;		// 座標
	DirectX::SimpleMath::Vector3 m_localVel;		// 速度
	DirectX::SimpleMath::Vector3 m_localAccel;		// 速度
	DirectX::SimpleMath::Quaternion m_localDir;		// 向き
	DirectX::SimpleMath::Matrix m_localMatrix;		// ワールド座標

private:						
	Transform* m_parent;					// 親の情報
	std::list<Transform*> m_childList;		// 子供のリストの情報
};