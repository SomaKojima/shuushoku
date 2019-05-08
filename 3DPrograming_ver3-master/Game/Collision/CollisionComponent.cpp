#include "../../pch.h"
#include "CollisionComponent.h"

/// <summary>
/// 更新処理
/// </summary>
/// <param name="elapsedTime"></param>
void CollisionComponent::Update(float elapsedTime)
{
	isHit = false;
}

bool CollisionComponent::Collision(CollisionComponent * col, DirectX::SimpleMath::Vector3& hitPos)
{
	bool isHit = false;

	// 衝突したか判定する(衝突した場合それぞれの衝突処理もする)
	switch (col->GetShape())
	{
		// 球
	case Collision::SHAPE_TYPE::SHAPE_TYPE_SPHERE:
		if (SphereCollision(*col->GetGameObject(), *col->GetSphere(), hitPos))
		{
			isHit = true;
		}
		break;

		// メッシュ
	case Collision::SHAPE_TYPE::SHAPE_TYPE_MESH:
		for (auto ite = col->GetTriangleList()->begin(); ite != col->GetTriangleList()->end(); ite++)
		{
			if (TriangleCollision(*col->GetGameObject(), (*ite), hitPos))
			{
				isHit = true;
			}
		}
		break;
	}

	// 衝突したときの処理
	if (isHit)
	{
		// 当たった
		this->SetHit(true);
		col->SetHit(true);
		// 衝突判定
		this->GetGameObject()->OnCollision(*col->GetGameObject(), col, hitPos);
		col->GetGameObject()->OnCollision(*col->GetGameObject(), this, hitPos);
	}

	return isHit;
}
