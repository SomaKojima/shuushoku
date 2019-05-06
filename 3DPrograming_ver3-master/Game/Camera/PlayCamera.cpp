#include "../../pch.h"
#include "PlayCamera.h"
#include "Mouse.h"
#include "../Object/GameObject.h"
#include "CameraManager.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

PlayCamera::PlayCamera(GameObject* player)
	:
	m_target(player),
	m_x(0),
	m_y(0)
{
}

void PlayCamera::Initialize()
{

}

void PlayCamera::Update(float elapsedTime)
{
	/*Vector3 eyeVec = Vector3::Transform(Vector3(0.0f, 3.0f, -5.0f), m_target->GetTransform().WorldDir());
	Vector3 eyePos = m_target->GetTransform().WorldMatrix().Translation() + eyeVec;

	SetPositionTarget(eyePos, m_target->GetTransform().WorldMatrix().Translation());*/


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

	// ----- �}�E�X�̍��W���擾���� -----
	POINT p;
	GetCursorPos(&p);

	// ----- �}�E�X�̈ړ��ʂ��擾���� -----
	Vector2 mouseVec = Vector2(p.x - centralX, p.y - centralY);
	mouseVec *= 0.1f;


	// ----- ��]���X�V -----
	m_x += XMConvertToRadians(mouseVec.x);
	m_y += XMConvertToRadians(mouseVec.y);

	if (m_y > XMConvertToRadians(90.0f))
	{
		m_y = XMConvertToRadians(90.0f);
	}
	else if (m_y < -XMConvertToRadians(90.0f))
	{
		m_y = -XMConvertToRadians(90.0f);
	}

	Quaternion q = Quaternion::CreateFromYawPitchRoll(-m_x, m_y, 0.0f);

	Quaternion dir = Quaternion::Identity;
	Vector3 upDir = Vector3::Transform(Vector3::Up, m_gameObject->GetTransform().WorldDir());
	float degree = mouseVec.x;
	Quaternion cameraDir = Quaternion::Identity;
	q = Quaternion::CreateFromYawPitchRoll(0.0f, m_y, 0.0f);
	if (mouseVec.x != 0)
	{
		dir = Quaternion::CreateFromAxisAngle(upDir, -XMConvertToRadians(degree));
	}
	m_gameObject->GetTransform().WorldDir(m_gameObject->GetTransform().WorldDir() * dir);
	cameraDir = q * m_gameObject->GetTransform().WorldDir();


	// ----- �}�E�X�̍��W���E�B���h�E�̒����ɌŒ肷�� -----
	SetCursorPos(centralX, centralY);

	// ----- �J�����̍��W�����߂� -----
	Vector3 eyeVec = Vector3::Transform(Vector3(0.0f, 0.0f, -10.0f), cameraDir) +
		Vector3::Transform(Vector3(0.0f, 2.0f * cos(m_y), 2.0f * sin(m_y)), m_gameObject->GetTransform().WorldDir());
	Vector3 eyePos = m_gameObject->GetTransform().WorldPos() + eyeVec;
	Vector3 target = m_gameObject->GetTransform().WorldPos() + Vector3::Transform(Vector3(0.0f, 0.0f, 10.0f), cameraDir);

	SetPositionTarget(eyePos, target);





	// �J�����Ǘ��̃r���[���X�V����
	CameraManager& cameraManager = CameraManager::GetInstace();
	cameraManager.SetView(Matrix::CreateLookAt(GetEyePosition(), GetTargetPosition(), GetUp()));
}

DirectX::SimpleMath::Vector3 PlayCamera::GetUp()
{
	Vector3 up = Vector3::Transform(Vector3::Up, m_target->GetTransform().WorldDir());
	return up;
}
