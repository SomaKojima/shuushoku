#include "../../pch.h"
#include "Down.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

Down::Down()
{
}

Down::~Down()
{
}

void Down::Excute(GameObject & obj)
{
	float speed = 0.2f;
	Vector3 vec = Vector3::Down * speed;
	Quaternion q = obj.GetTransform().WorldDir();
	Vector3 accel = Vector3::Transform(vec, q);
	obj.GetTransform().WorldAccel(accel);
}
