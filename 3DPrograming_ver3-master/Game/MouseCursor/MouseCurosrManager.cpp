/// <summary>
/// �C���N���[�h
/// </summary>
#include "../../pch.h"
#include "MouseCurosrManager.h"
#include "../SubGame.h"

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

/// <summary>
/// �X�V
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
/// ������ς���
/// </summary>
/// <param name="isVisible"></param>
void MouseCursorManager::ChangeVisible(bool isVisible)
{
	m_isVisible = isVisible;
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
/// ������ς���
/// </summary>
void MouseCursorManager::ChangeVisible()
{
	m_isVisible = !m_isVisible;
	ChangeVisible(m_isVisible);
}

/// <summary>
/// ������ς���
/// </summary>
/// <param name="isMove"></param>
void MouseCursorManager::ChangeMoveMode(bool isMove)
{
	m_isMove = isMove;
}

/// <summary>
/// ������ς���
/// </summary>
void MouseCursorManager::ChangeMoveMode()
{
	m_isMove = !m_isMove;
}

/// <summary>
/// �}�E�X�J�[�\������ʒ����Ɉړ�������
/// </summary>
void MouseCursorManager::MoveCenter()
{
	// ----- �E�B���h�E�̏�񂪎擾�ł��Ȃ��ꍇ -----
	if (!GetActiveWindow()) return;

	// ���g�E�B���h�E���A�N�e�B�u���ǂ����𔻒�
	SubGame& subGame = SubGame::GetInstace();
	if (GetActiveWindow() != subGame.GetWindow()) return;

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
