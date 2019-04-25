/// <summary>
/// CollisionComponent.h
/// 
/// �����:2018/10/26
/// �����:���� �D�V
/// </summary>

/// <summary>
/// ���d�C���N���[�h�̖h�~
/// </summary>
#pragma once

/// <summary>
/// �w�b�_�̃C���N���[�h
/// </summary>
#include "../Component/Component.h"
#include "../Collision/Collision.h"

/// <summary>
/// ���̓����蔻��̃R���|�[�l���g�N���X
/// </summary>
class CollisionComponent : public Component
{
public:
	CollisionComponent() :isHit(false) {};
	~CollisionComponent() {};

	// �X�V
	virtual void Update(float elapsedTime) override;

	// �����蔻��
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
