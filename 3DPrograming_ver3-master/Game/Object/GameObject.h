#pragma once

#include "Transform.h"
#include "../Utility/BidirectionalList.h"

/// <summary>
/// �Q�[���I�u�W�F�N�g�̃N���X
/// </summary>
class GameObject : public BidirectionalList<GameObject>
{
public:
	// �R���X�g���N�^
	GameObject();
	// �f�X�g���N�^
	virtual ~GameObject();

public:
	// ����������
	virtual void Initialize() = 0;
	// �X�V����
	virtual void Update(float elapsedTime) = 0;
	// �`�揈��
	virtual void Renderer() = 0;
	// �I������
	virtual void Finalize() = 0;
	// �q���̃��X�g�ɒǉ�����
	void AddChild(GameObject* gameObject) { transform.AddChild(&gameObject->transform); }
public:
	// �ό`
	Transform transform;
};