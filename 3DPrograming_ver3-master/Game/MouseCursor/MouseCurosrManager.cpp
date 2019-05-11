/// <summary>
/// インクルード
/// </summary>
#include "../../pch.h"
#include "MouseCurosrManager.h"
#include "../SubGame.h"

/// <summary>
/// コンストラクタ
/// </summary>
MouseCursorManager::MouseCursorManager()
	:
	m_isVisible(true),
	m_isMove(true)
{
}

/// <summary>
/// デストラクタ
/// </summary>
MouseCursorManager::~MouseCursorManager()
{
}

/// <summary>
/// 更新
/// </summary>
/// <param name="elapsedTime"></param>
void MouseCursorManager::Update(float elapsedTime)
{
	if (!m_isMove)
	{
		MoveCenter();
	}
}

/// <summary>
/// 可視化を変える
/// </summary>
/// <param name="isVisible"></param>
void MouseCursorManager::ChangeVisible(bool isVisible)
{
	m_isVisible = isVisible;
	if (m_isVisible)
	{
		// マウスの表示
		while (ShowCursor(TRUE) < 0);
	}
	else
	{
		// マウスの非表示
		while (ShowCursor(FALSE) >= 0);
	}
}

/// <summary>
/// 可視化を変える
/// </summary>
void MouseCursorManager::ChangeVisible()
{
	m_isVisible = !m_isVisible;
	ChangeVisible(m_isVisible);
}

/// <summary>
/// 動きを変える
/// </summary>
/// <param name="isMove"></param>
void MouseCursorManager::ChangeMoveMode(bool isMove)
{
	m_isMove = isMove;
}

/// <summary>
/// 動きを変える
/// </summary>
void MouseCursorManager::ChangeMoveMode()
{
	m_isMove = !m_isMove;
}

/// <summary>
/// マウスカーソルを画面中央に移動させる
/// </summary>
void MouseCursorManager::MoveCenter()
{
	// ----- ウィンドウの情報が取得できない場合 -----
	if (!GetActiveWindow()) return;

	// 自身ウィンドウがアクティブ化どうかを判定
	SubGame& subGame = SubGame::GetInstace();
	if (GetActiveWindow() != subGame.GetWindow()) return;

	// ----- ウィンドウの長方形(Rectangle)の情報を取得する
	RECT wRect;
	GetWindowRect(GetActiveWindow(), &wRect);
	int width = (wRect.right - wRect.left) / 2;
	int height = (wRect.bottom - wRect.top) / 2;

	// ----- ウィンドウの中心座標を取得する -----
	int centralX = wRect.left + width;
	int centralY = wRect.top + height;
	// ----- マウスの座標をウィンドウの中央に固定する -----
	SetCursorPos(centralX, centralY);
}
