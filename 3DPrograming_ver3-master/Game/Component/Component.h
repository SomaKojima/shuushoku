#pragma once

#include "../../StepTimer.h"
#include "../../Game.h"
#include "../Object/GameObject.h"
#include "../Collision/Collision.h"

class CollisionComponent;

/// <summary>
/// コンポーネントクラス
/// </summary>
class Component
{
protected:
	// コンストラクタ
	Component() : m_gameObject(nullptr){}

public:
	// 仮想デストラクタ
	virtual ~Component() {}

	// 初期化
	virtual void Initialize() {}
	// 更新
	virtual void Update(float elapsedTime) {}
	// 遅延更新
	virtual void LateUpdate(float elapsedTime) {}
	// 描画
	virtual void Render() {}
	// 終了
	virtual void Finalize() {}

	// 球との当たり判定
	virtual void OnSphereCollision(GameObject& obj, const Collision::Sphere& sphere, DirectX::SimpleMath::Vector3& hitPos) {}
	// 面との当たり判定
	virtual void OnTriangleCollision(GameObject& obj, const Collision::Triangle& triangle, DirectX::SimpleMath::Vector3& hitPos) {}


	// 当たり判定の処理
	virtual void OnCollision(GameObject& obj, DirectX::SimpleMath::Vector3& hitPos) {}

	// オブジェクトを設定する
	void SetGameObject(GameObject* obj) { m_gameObject = obj; }
	// オブジェクトを取得する
	GameObject* GetGameObject() { return m_gameObject; }
protected:
	// 自身のコンポーネントをアタッチしているオブジェクト
	GameObject* m_gameObject;
};