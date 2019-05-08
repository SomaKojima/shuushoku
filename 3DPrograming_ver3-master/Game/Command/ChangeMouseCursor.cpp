#include "../../pch.h"
#include "ChangeMouseCursor.h"
#include "../MouseCursor/MouseCurosrManager.h"

ChangeMouseCursor::ChangeMouseCursor()
{
}

ChangeMouseCursor::~ChangeMouseCursor()
{
}

void ChangeMouseCursor::Excute(GameObject & obj)
{
	MouseCursorManager& mouseCursorManager = MouseCursorManager::GetInstace();

	mouseCursorManager.ChangeVisible();
	mouseCursorManager.ChangeMoveMode();
}
