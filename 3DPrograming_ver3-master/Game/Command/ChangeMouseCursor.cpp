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
		// �}�E�X�̕\��
		while (ShowCursor(TRUE) < 0);
	}
	else
	{
		// �}�E�X�̔�\��
		while (ShowCursor(FALSE) >= 0);
	}
}
