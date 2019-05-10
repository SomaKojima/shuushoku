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
	// ‘¬“x‚É–€ŽC‚ð‰Á‚¦‚é
	Vector3 localVel = m_gameObject->GetTransform().LocalVel();
	float friction = 0.9f;

	localVel.x *= friction;
	localVel.z *= friction;
	m_gameObject->GetTransform().LocalVel(localVel);

	// ‰Á‘¬“x‚É–€ŽC‚ð‰Á‚¦‚é
	Vector3 localAccel = m_gameObject->GetTransform().LocalAccel();
	localAccel.x *= friction;
	localAccel.z *= friction;
	m_gameObject->GetTransform().LocalAccel(localAccel);
}
