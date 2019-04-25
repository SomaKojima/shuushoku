#include "../../pch.h"
#include "Component.h"
#include "../Collision/CollisionComponent.h"

bool Component::OnShapeCollision(GameObject& obj, CollisionComponent * col, DirectX::SimpleMath::Vector3 & hitPos)
{
	switch (col->GetShape())
	{
	case Collision::SHAPE_TYPE::SHAPE_TYPE_SPHERE:
		return OnSphereCollision(obj, *col->GetSphere(), hitPos);
		break;
	case Collision::SHAPE_TYPE::SHAPE_TYPE_MESH:
		for (auto ite = col->GetTriangleList()->begin(); ite != col->GetTriangleList()->end(); ite++)
		{
			if (OnTriangleCollision(obj, (*ite), hitPos))
			{
				return true;
			}
		}
		break;
	}
	return false;
}
