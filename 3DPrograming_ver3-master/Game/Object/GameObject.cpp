#include "../../pch.h"
#include "GameObject.h"
#include "../Component/Component.h"

using namespace std;
using namespace DirectX;
using namespace DirectX::SimpleMath;

GameObject::GameObject() 
	: 
	BidirectionalList<GameObject>(this)
{
}

GameObject::~GameObject()
{
}

void GameObject::Initialize()
{
	// �R���|�[�l���g�̏�����
	for (auto ite = m_componentList.begin(); ite != m_componentList.end(); ite++)
	{
		(*ite)->SetGameObject(this);
		(*ite)->Initialize();
	}
}

void GameObject::Update(float elapsedTime)
{
	// �ό`�̍X�V
	m_transform.Update(elapsedTime);
	// �R���|�[�l���g�̍X�V
	for (auto ite = m_componentList.begin(); ite != m_componentList.end(); ite++)
	{
		(*ite)->Update(elapsedTime);
		(*ite)->LateUpdate(elapsedTime);
	}
}

void GameObject::Render()
{
	// �R���|�[�l���g�̕`��
	for (auto ite = m_componentList.begin(); ite != m_componentList.end(); ite++)
	{
		(*ite)->Render();
	}
}

void GameObject::Finalize()
{
	// �R���|�[�l���g�̏I��
	for (auto ite = m_componentList.begin(); ite != m_componentList.end(); ite++)
	{
		(*ite)->Finalize();
	}
	m_componentList.clear();
}
