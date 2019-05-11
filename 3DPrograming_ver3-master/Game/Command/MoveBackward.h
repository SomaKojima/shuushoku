#pragma once

#include "Command.h"

/// <summary>
/// 後退コマンドのクラス
/// </summary>
class MoveBackward : public Command
{
public:
	// コンストラクタ
	MoveBackward();
	// デストラクタ
	~MoveBackward();

public:
	// 実行関数
	void Excute(GameObject& obj) override;
};
