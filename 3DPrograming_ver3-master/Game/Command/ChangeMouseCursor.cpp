#include "../../pch.h"
#include "ChangeMouseCursor.h"

ChangeMouseCursor::ChangeMouseCursor()
	:
	isEnable(false)
{
}

ChangeMouseCursor::~ChangeMouseCursor()
{
}

void ChangeMouseCursor::Excute(GameObject & obj)
{
	isEnable = !isEnable;

	if (isEnable)
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
