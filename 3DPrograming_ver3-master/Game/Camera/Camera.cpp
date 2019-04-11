#include "../../pch.h"
#include "Camera.h"
#include "PlayCamera.h"

Camera::Camera(GameObject* target)
	:
	m_target(target)
{
}

Camera::~Camera()
{
	m_target = nullptr;
}

void Camera::Instance()
{
	// �J�����̃R���|�[�l���g���쐬
	Component* playCamera = new PlayCamera(m_target);
	AddComponent(playCamera);
}
