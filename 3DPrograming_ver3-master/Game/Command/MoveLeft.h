#pragma once

#include "Command.h"

/// <summary>
/// 左移動コマンドのクラス
/// </summary>
class MoveLeft : public Command
{
public:
	// コンストラクタ
	MoveLeft();
	// デストラクタ
	~MoveLeft();

public:
	// 実行関数
	void Excute(GameObject& obj) override;
};

