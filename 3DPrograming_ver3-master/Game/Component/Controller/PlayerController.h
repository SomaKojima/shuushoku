#pragma once

#include "../Component.h"
#include "../../Command/InputHandler.h"
#include "../../Command/Command.h"

/// <summary>
/// プレイヤーの操作のコンポーネント
/// </summary>
class PlayerController : public Component
{
public:
	// コンストラクタ
	PlayerController();
	// デストラクタ
	~PlayerController();

public:
	// 更新処理
	void Update(float elapsedTime) override;

private:
	InputHandler inputHnadler;
};