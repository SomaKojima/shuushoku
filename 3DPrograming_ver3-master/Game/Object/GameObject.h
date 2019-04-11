#pragma once

#include <list>
#include "Transform.h"
#include "../Utility/BidirectionalList.h"

class Component;

/// <summary>
/// ゲームオブジェクトのクラス
/// </summary>
class GameObject : public BidirectionalList<GameObject>
{
public:
	// コンストラクタ
	GameObject();
	// デストラクタ
	virtual ~GameObject();

public:
	// 生成関数
	virtual void Instance() = 0;

public:
	// 初期化処理
	void Initialize();
	// 更新処理
	void Update(float elapsedTime);
	// 描画処理
	void Render();
	// 終了処理
	void Finalize();

public:
	// 子供のリストに追加する
	void AddChild(GameObject* gameObject) { m_transform.AddChild(&gameObject->m_transform); }

	// コンポーネントのクラスに追加する
	void AddComponent(Component* component) { m_componentList.push_back(component); }
	/// <summary>
	/// コンポーネントを取得する関数
	/// </summary>
	template<class T>
	inline T* GetComponent();
	template<class T>
	inline T* GetComponent(Component* component);
	template<class T>
	inline std::list<T*> GetComponentList();

	// 変形の取得
	Transform& GetTransform() { return m_transform; }
private:
	// 変形
	Transform m_transform;
	// コンポーネントのリスト
	std::list<Component*> m_componentList;
};

/// <summary>
/// コンポーネントのリストから一つのコンポーネントを取得する
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
/// 引数のポインタからコンポーネントを取得する
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
/// コンポーネントのリストから複数のコンポーネントをリストで取得する
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
