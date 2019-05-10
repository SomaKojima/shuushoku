#pragma once
#include "../Utility/Singleton.h"

class MouseCursorManager : public Singleton<MouseCursorManager>
{
public:
	MouseCursorManager();
	~MouseCursorManager();

public:
	void Update(float elapsedTime);
	void ChangeVisible(bool isVisible);
	void ChangeVisible();
	void ChangeMoveMode(bool isMove);
	void ChangeMoveMode();
	void MoveCenter();

	bool GetIsVisible() { return m_isVisible; }
	bool GetIsMove() { return m_isMove; }

private:
	bool m_isVisible;
	bool m_isMove;
};