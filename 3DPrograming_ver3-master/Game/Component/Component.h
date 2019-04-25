#pragma once

#include "../../StepTimer.h"
#include "../../Game.h"
#include "../Object/GameObject.h"
#include "../Collision/Collision.h"

class CollisionComponent;

/// <summary>
/// �R���|�[�l���g�N���X
/// </summary>
class Component
{
protected:
	// �R���X�g���N�^
	Component() : m_gameObject(nullptr){}

public:
	// ���z�f�X�g���N�^
	virtual ~Component() {}

	// ������
	virtual void Initialize() {}
	// �X�V
	virtual void Update(float elapsedTime) {}
	// �x���X�V
	virtual void LateUpdate(float elapsedTime) {}
	// �`��
	virtual void Render() {}
	// �I��
	virtual void Finalize() {}

	bool OnShapeCollision(GameObject& obj, CollisionComponent* col, DirectX::SimpleMath::Vector3& hitPos);

	// ���Ƃ̓����蔻��
	virtual bool OnSphereCollision(GameObject& obj, const Collision::Sphere& sphere, DirectX::SimpleMath::Vector3& hitPos) { return false; }
	// �ʂƂ̓����蔻��
	virtual bool OnTriangleCollision(GameObject& obj, const Collision::Triangle& triangle, DirectX::SimpleMath::Vector3& hitPos) { return false; }

	// �����蔻��̏���
	virtual void OnCollision(GameObject& obj, DirectX::SimpleMath::Vector3& hitPos) {}

	// �I�u�W�F�N�g��ݒ肷��
	void SetGameObject(GameObject* obj) { m_gameObject = obj; }
	// �I�u�W�F�N�g���擾����
	GameObject* GetGameObject() { return m_gameObject; }
protected:
	// ���g�̃R���|�[�l���g���A�^�b�`���Ă���I�u�W�F�N�g
	GameObject* m_gameObject;
};