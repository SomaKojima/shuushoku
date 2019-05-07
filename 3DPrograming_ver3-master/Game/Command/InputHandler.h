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

	// Zキーのコマンド
	Command* m_keyZ;
	// Xキーのコマンド
	Command* m_keyX;

	// スペースキーのコマンド
	Command* m_keySpace;

	// 入力ハンドルを取得
	std::vector<Command*> GetInputHnadle();

private:
};