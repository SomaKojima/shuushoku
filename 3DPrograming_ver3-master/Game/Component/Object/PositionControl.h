#pragma once

#include "../Component.h"

/// <summary>
/// 摩擦のコンポーネント
/// </summary>
class PositionControl : public Component
{
public:
	// コンストラクタ
	PositionControl();
	// デストラクタ
	~PositionControl();

public:
	// 更新処理
	void Update(float elapsedTime) override;
	
	// 面との当たり判定
	void OnTriangleCollision(GameObject& obj, const Collision::Triangle& triangle, DirectX::SimpleMath::Vector3& hitPos);

private:
	DirectX::SimpleMath::Vector3 m_normal;
	bool m_isWallHit;
};