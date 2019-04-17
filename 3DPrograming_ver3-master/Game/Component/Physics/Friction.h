#pragma once

#include "../Component.h"

/// <summary>
/// 摩擦のコンポーネント
/// </summary>
class Friction : public Component
{
public:
	// コンストラクタ
	Friction();
	// デストラクタ
	~Friction();

public:
	// 更新処理
	void Update(float elapsedTime) override;
private:
};