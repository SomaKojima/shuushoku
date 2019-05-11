#pragma once

#include "Command.h"

/// <summary>
/// 右移動コマンドのクラス
/// </summary>
class MoveRight : public Command
{
public:
	// コンストラクタ
	MoveRight();
	// デストラクタ
	~MoveRight();

public:
	// 実行関数
	void Excute(GameObject& obj) override;
};