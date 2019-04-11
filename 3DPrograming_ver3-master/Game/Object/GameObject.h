#pragma once

#include <list>
#include "Transform.h"
#include "../Utility/BidirectionalList.h"

class Component;

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
	// �����֐�
	virtual void Instance() = 0;

public:
	// ����������
	void Initialize();
	// �X�V����
	void Update(float elapsedTime);
	// �`�揈��
	void Render();
	// �I������
	void Finalize();

public:
	// �q���̃��X�g�ɒǉ�����
	void AddChild(GameObject* gameObject) { m_transform.AddChild(&gameObject->m_transform); }

	// �R���|�[�l���g�̃N���X�ɒǉ�����
	void AddComponent(Component* component) { m_componentList.push_back(component); }
	/// <summary>
	/// �R���|�[�l���g���擾����֐�
	/// </summary>
	template<class T>
	inline T* GetComponent();
	template<class T>
	inline T* GetComponent(Component* component);
	template<class T>
	inline std::list<T*> GetComponentList();

	// �ό`�̎擾
	Transform& GetTransform() { return m_transform; }
private:
	// �ό`
	Transform m_transform;
	// �R���|�[�l���g�̃��X�g
	std::list<Component*> m_componentList;
};

/// <summary>
/// �R���|�[�l���g�̃��X�g�����̃R���|�[�l���g���擾����
/// </summary>
template<class T>
inline T * GameObject::GetComponent()
{
	T* sub = nullptr;
	for (auto ite = m_componentlist.begin(); ite != m_componentlist.end(); ite++)
	{
		sub = dynamic_cast<T*>((*ite));
		if (sub)
		{
			return sub;
		}
	}
	return nullptr;
}

/// <summary>
/// �����̃|�C���^����R���|�[�l���g���擾����
/// </summary>
template<class T>
inline T * GameObject::GetComponent(Component * component)
{
	T* sub = nullptr;
	for (auto ite = m_componentlist.begin(); ite != m_componentlist.end(); ite++)
	{
		sub = dynamic_cast<T*>((*ite));
		if (sub == component)
		{
			return sub;
		}
	}
	return nullptr;
}

/// <summary>
/// �R���|�[�l���g�̃��X�g���畡���̃R���|�[�l���g�����X�g�Ŏ擾����
/// </summary>
template<class T>
inline std::list<T*> GameObject::GetComponentList()
{
	T* sub = nullptr;
	std::list<T*> list;
	for (auto ite = m_componentlist.begin(); ite != m_componentlist.end(); ite++)
	{
		sub = dynamic_cast<T*>((*ite));
		if (sub)
		{
			list.push_back(sub);
		}
	}
	return list;
}
