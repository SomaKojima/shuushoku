#pragma once

/// <summary>
/// 使い方の例
/// </summary>

/// <summary>
/// 登録されるオブジェクトクラス（リストの要素となるクラス）
/// </summary>
/*

class EntityOfTree : public BidirectionalList<Entity>
{
public:
	EntityOfTree(Entity* obj) : BidirectionalList(obj) {}
	~EntityOfTree() {}

};

*/

/// <summary>
/// 登録する先のクラス
/// </summary>
/*

class EntityList : public BidirectionalList<Entity>::RegisterTo
{
public:
	EntityList() {}
	~EntityList() {}
};

*/

/// <summary>
/// 登録されるオブジェクトクラス（リストの要素となるクラス）
/// </summary>
template<class T2> class BidirectionalList
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="obj"></param>
	BidirectionalList(T2* obj) : m_pPre(nullptr), m_pNext(nullptr), m_pRegisterTo(nullptr), m_pObj(obj) { }

	/// <summary>
	/// デストラクタ
	/// </summary>
	virtual ~BidirectionalList() { m_pPre = nullptr; m_pNext = nullptr; m_pRegisterTo = nullptr; m_pObj = nullptr; }

public:
	/// <summary>
	/// 登録先のクラス
	/// </summary>
	class RegisterTo
	{
	public:
		RegisterTo() : m_pTop(nullptr) {}
		virtual ~RegisterTo() {}

		bool Add(BidirectionalList<T2>* obj);

		void SetTop(BidirectionalList<T>* top) { m_pTop = top; }
		BidirectionalList<T2>* GetTop() { return m_pTop; }

		void Clear();

	protected:
		BidirectionalList<T2>* m_pTop;
	};

public:
	// リスト先のクラスから離れる(リストから削除)
	bool Remove();

	// getter
	BidirectionalList<T2>* GetPre() { return m_pPre; }
	BidirectionalList<T2>* GetNext() { return m_pNext; }
	RegisterTo* GetRegisterTo() { return m_pRegisterTo; }
	T2* GetObj() { return m_pObj; }

private:
	// setter
	void SetPre(T* bl) { m_pPre = bl; }
	void SetNext(T* bl) { m_pNext = bl; }
	void SetRegisterTo(RegisterTo* registerTo) { m_pRegisterTo = registerTo; }

private:
	BidirectionalList<T2>* m_pPre;
	BidirectionalList<T2>* m_pNext;

	RegisterTo* m_pRegisterTo;

	// 登録されているオブジェクトの削除
	T2* m_pObj;
};

template<class T2>
inline bool BidirectionalList<T2>::Remove()
{
	// 登録されていない場合
	if (!m_pRegisterTo)
	{
		return false;
	}

	// 前のポインタの処理
	if (!m_pPre)
	{
		m_pRegisterTo->SetTop(m_pNext);
	}
	else
	{
		m_pPre->SetNext(m_pNext);
	}

	// 次のポインタの処理
	if (m_pNext)
	{
		m_pNext->SetPre(m_pPre);
	}

	m_pPre = nullptr;
	m_pNext = nullptr;

	m_pRegisterTo = nullptr;
	return true;
}

template<class T2>
inline bool BidirectionalList<T2>::RegisterTo::Add(BidirectionalList<T2>* obj)
{
	// 二重登録防止
	if (obj->GetRegisterTo() == this)
	{
		return false;
	}

	obj->Remove();
	if (!m_pTop)
	{
		obj->SetRegisterTo(this);
		obj->SetPre(nullptr);
		obj->SetNext(nullptr);
		m_pTop = obj;
		return true;
	}

	obj->SetRegisterTo(this);
	obj->SetPre(nullptr);
	obj->SetNext(m_pTop);

	// 現在先頭のOFTを変える
	m_pTop->SetPre(obj);
	m_pTop = obj;

	return true;
}

template<class T2>
inline void BidirectionalList<T2>::RegisterTo::Clear()
{
	while (m_pTop)
	{
		m_pTop->Remove();
	}
}
