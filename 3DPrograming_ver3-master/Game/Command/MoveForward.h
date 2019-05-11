#pragma once

#include "Command.h"

/// <summary>
/// 前進コマンドのクラス
/// </summary>
class MoveForward : public Command
{
public:
	// コンストラクタ
	MoveForward();
	~MoveForward();

public:
	// 実行関数
	void Excute(GameObject& obj) override;
};