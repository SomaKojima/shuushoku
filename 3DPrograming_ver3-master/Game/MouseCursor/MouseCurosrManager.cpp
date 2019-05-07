/// <summary>
/// �C���N���[�h
/// </summary>
#include "../../pch.h"
#include "MouseCurosrManager.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
MouseCursorManager::MouseCursorManager()
	:
	m_isVisible(true),
	m_isMove(true)
{
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
MouseCursorManager::~MouseCursorManager()
{
}

void MouseCursorManager::Update(float elapsedTime)
{
	if (!m_isMove)
	{
		// ----- �E�B���h�E�̏�񂪎擾�ł��Ȃ��ꍇ -----
		if (!GetActiveWindow())
		{
			return;
		}

		// ----- �E�B���h�E�̒����`(Rectangle)�̏����擾����
		RECT wRect;
		GetWindowRect(GetActiveWindow(), &wRect);
		int width = (wRect.right - wRect.left) / 2;
		int height = (wRect.bottom - wRect.top) / 2;

		// ----- �E�B���h�E�̒��S���W���擾���� -----
		int centralX = wRect.left + width;
		int centralY = wRect.top + height;
		// ----- �}�E�X�̍��W���E�B���h�E�̒����ɌŒ肷�� -----
		SetCursorPos(centralX, centralY);
	}
}

/// <summary>
/// ������ς���
/// </summary>
void MouseCursorManager::ChangeVisible()
{
	m_isVisible = !m_isVisible;

	if (m_isVisible)
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

/// <summary>
/// ������ς���
/// </summary>
void MouseCursorManager::ChangeMoveMode()
{
	m_isMove = !m_isMove;

}
