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
	// コンポーネントの初期化
	for (auto ite = m_componentList.begin(); ite != m_componentList.end(); ite++)
	{
		(*ite)->SetGameObject(this);
		(*ite)->Initialize();
	}
}

void GameObject::Update(float elapsedTime)
{
	// 変形の更新
	m_transform.Update(elapsedTime);
	// コンポーネントの更新
	for (auto ite = m_componentList.begin(); ite != m_componentList.end(); ite++)
	{
		(*ite)->Update(elapsedTime);
		(*ite)->LateUpdate(elapsedTime);
	}
}

void GameObject::Render()
{
	// コンポーネントの描画
	for (auto ite = m_componentList.begin(); ite != m_componentList.end(); ite++)
	{
		(*ite)->Render();
	}
}

void GameObject::Finalize()
{
	// コンポーネントの終了
	for (auto ite = m_componentList.begin(); ite != m_componentList.end(); ite++)
	{
		(*ite)->Finalize();
	}
	m_componentList.clear();
}
