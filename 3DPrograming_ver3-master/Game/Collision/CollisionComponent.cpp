#include "../../pch.h"
#include "CollisionComponent.h"

/// <summary>
/// XVˆ—
/// </summary>
/// <param name="elapsedTime"></param>
void CollisionComponent::Update(float elapsedTime)
{
	isHit = false;
}

bool CollisionComponent::Collision(CollisionComponent * col, DirectX::SimpleMath::Vector3& hitPos)
{
	switch (col->GetShape())
	{
	case Collision::SHAPE_TYPE::SHAPE_TYPE_SPHERE:
			return SphereCollision(*col->GetSphere(), hitPos);
			break;
	case Collision::SHAPE_TYPE::SHAPE_TYPE_MESH:
			for (auto ite = col->GetTriangleList()->begin(); ite != col->GetTriangleList()->end(); ite++)
			{
				if (TriangleCollision((*ite), hitPos))
				{
					return true;
				}
			}
			break;
	}
	return false;
}
