#pragma once

#include "Command.h"

/// <summary>
/// 上昇コマンドのクラス
/// </summary>
class Up : public Command
{
public:
	// コンストラクタ
	Up();
	~Up();

public:
	// 実行関数
	void Excute(GameObject& obj) override;
};