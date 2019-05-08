#include "../../pch.h"
#include "CollisionComponent.h"

/// <summary>
/// �X�V����
/// </summary>
/// <param name="elapsedTime"></param>
void CollisionComponent::Update(float elapsedTime)
{
	isHit = false;
}

bool CollisionComponent::Collision(CollisionComponent * col, DirectX::SimpleMath::Vector3& hitPos)
{
	bool isHit = false;

	// �Փ˂��������肷��(�Փ˂����ꍇ���ꂼ��̏Փˏ���������)
	switch (col->GetShape())
	{
		// ��
	case Collision::SHAPE_TYPE::SHAPE_TYPE_SPHERE:
		if (SphereCollision(*col->GetGameObject(), *col->GetSphere(), hitPos))
		{
			isHit = true;
		}
		break;

		// ���b�V��
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

	// �Փ˂����Ƃ��̏���
	if (isHit)
	{
		// ��������
		this->SetHit(true);
		col->SetHit(true);
		// �Փ˔���
		this->GetGameObject()->OnCollision(*col->GetGameObject(), col, hitPos);
		col->GetGameObject()->OnCollision(*col->GetGameObject(), this, hitPos);
	}

	return isHit;
}
