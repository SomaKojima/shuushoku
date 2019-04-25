/// <summary>
/// CollisionComponent.h
/// 
/// 制作日:2018/10/26
/// 制作者:小嶋 颯天
/// </summary>

/// <summary>
/// 多重インクルードの防止
/// </summary>
#pragma once

/// <summary>
/// ヘッダのインクルード
/// </summary>
#include "../Component/Component.h"
#include "../Collision/Collision.h"

/// <summary>
/// 球の当たり判定のコンポーネントクラス
/// </summary>
class CollisionComponent : public Component
{
public:
	CollisionComponent() :isHit(false) {};
	~CollisionComponent() {};

	// 更新
	virtual void Update(float elapsedTime) override;

	// 当たり判定
	bool Collision(CollisionComponent* col, DirectX::SimpleMath::Vector3& hitPos);
	virtual bool SphereCollision(const Collision::Sphere& sphere, DirectX::SimpleMath::Vector3& hitPos) = 0;
	virtual bool TriangleCollision(const Collision::Triangle& triangle, DirectX::SimpleMath::Vector3& hitPos) = 0;


	void SetHit(bool flag) { isHit = flag; }
	bool IsHit() { return isHit; }

	Collision::SHAPE_TYPE GetShape() { return m_shapeType; }

	virtual const Collision::Sphere* GetSphere() { return nullptr; }
	virtual const Collision::Segment* GetSegment() { return nullptr; }
	virtual const Collision::Plane* GetPlane() { return nullptr; }
	virtual const Collision::Triangle* GetTriangle() { return nullptr; }
	virtual const std::list<Collision::Triangle>* GetTriangleList() { return nullptr; }

private:
	bool isHit;
	Collision::SHAPE_TYPE m_shapeType;
};
