#pragma once

#include "Transform.h"
#include "../Utility/BidirectionalList.h"

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
	// 初期化処理
	virtual void Initialize() = 0;
	// 更新処理
	virtual void Update(float elapsedTime) = 0;
	// 描画処理
	virtual void Renderer() = 0;
	// 終了処理
	virtual void Finalize() = 0;
	// 子供のリストに追加する
	void AddChild(GameObject* gameObject) { transform.AddChild(&gameObject->transform); }
public:
	// 変形
	Transform transform;
};