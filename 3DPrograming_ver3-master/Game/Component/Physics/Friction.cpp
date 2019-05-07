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
	localVel.x *= 0.5f;
	localVel.z *= 0.5f;
	localVel.y *= 0.5f;
	m_gameObject->GetTransform().LocalVel(localVel);

	// ‰Á‘¬“x‚É–€ŽC‚ð‰Á‚¦‚é
	Vector3 localAccel = m_gameObject->GetTransform().LocalAccel();
	localAccel.x *= 0.5f;
	localAccel.z *= 0.5f;
	localAccel.y *= 0.5f;
	m_gameObject->GetTransform().LocalAccel(localAccel);
}
