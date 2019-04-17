#pragma once

#include <vector>
#include "Command.h"


class InputHandler
{
public:
	// コンストラクタ
	InputHandler();
	// デストラクタ
	~InputHandler();

public:
	// 上キーのコマンド
	Command* m_keyUpArrow;

	// 入力ハンドルを取得
	std::vector<Command*> GetInputHnadle();

private:
};