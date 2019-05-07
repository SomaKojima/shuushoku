#pragma once

#include "Command.h"

/// <summary>
/// 下降コマンドのクラス
/// </summary>
class Down : public Command
{
public:
	// コンストラクタ
	Down();
	~Down();

public:
	// 実行関数
	void Excute(GameObject& obj) override;
};
