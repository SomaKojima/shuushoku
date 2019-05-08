#pragma once

#include "Command.h"

/// <summary>
/// マウスカーソルを変更するコマンドのクラス
/// </summary>
class ChangeMouseCursor : public Command
{
public:
	// コンストラクタ
	ChangeMouseCursor();
	~ChangeMouseCursor();

public:
	// 実行関数
	void Excute(GameObject& obj) override;

};