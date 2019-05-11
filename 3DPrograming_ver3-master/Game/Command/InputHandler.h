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
	// Wキーのコマンド
	Command* m_keyW;
	// Aキーのコマンド
	Command* m_keyA;
	// Sキーのコマンド
	Command* m_keyS;
	// Dキーのコマンド
	Command* m_keyD;

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