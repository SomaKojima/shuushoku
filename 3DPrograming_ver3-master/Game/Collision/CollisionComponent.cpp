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

bool CollisionComponent::Collision(CollisionComponent * col, Collision::SHAPE_TYPE type, DirectX::SimpleMath::Vector3& hitPos)
{
	switch (type)
	{
		case Collision::SHAPE_TYPE::SPHERE:
			return SphereCollision(*col->GetSphere(), hitPos);
			break;
		case Collision::SHAPE_TYPE::MESH:
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
