#pragma once
#include "../Utility/Singleton.h"

class MouseCursorManager : public Singleton<MouseCursorManager>
{
public:
	MouseCursorManager();
	~MouseCursorManager();

public:
	void Update(float elapsedTime);
	void ChangeVisible();
	void ChangeMoveMode();

private:
	bool m_isVisible;
	bool m_isMove;
};