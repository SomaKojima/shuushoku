#include "../../pch.h"
#include "Friction.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

Friction::Friction()
{
}

Friction::~Friction()
{
}

void Friction::LateUpdate(float elapsedTime)
{
	// 速度に摩擦を加える
	Vector3 localVel = m_gameObject->GetTransform().LocalVel();
	localVel.x *= 0.5f;
	localVel.z *= 0.5f;
	m_gameObject->GetTransform().LocalVel(localVel);

	// 加速度に摩擦を加える
	Vector3 localAccel = m_gameObject->GetTransform().LocalAccel();
	localAccel.x *= 0.5f;
	localAccel.z *= 0.5f;
	m_gameObject->GetTransform().LocalAccel(localAccel);
}
