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
		if (SphereCollision(*col->GetSphere(), hitPos))
		{
			isHit = true;
			for (auto ite = m_gameObject->GetComponentList().begin(); ite != m_gameObject->GetComponentList().end(); ite++)
			{
				OnSphereCollision(*col->GetGameObject(), *col->GetSphere(), hitPos);
			}
		}
		break;

		// ���b�V��
	case Collision::SHAPE_TYPE::SHAPE_TYPE_MESH:
		for (auto ite = col->GetTriangleList()->begin(); ite != col->GetTriangleList()->end(); ite++)
		{
			if (TriangleCollision((*ite), hitPos))
			{
				isHit = true;
				for (auto ite2 = m_gameObject->GetComponentList().begin(); ite2 != m_gameObject->GetComponentList().end(); ite2++)
				{
					OnTriangleCollision(*col->GetGameObject(), (*ite), hitPos);
				}
				break;
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
