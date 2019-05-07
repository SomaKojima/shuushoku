#include "../../pch.h"
#include "Up.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

Up::Up()
{
}

Up::~Up()
{
}

void Up::Excute(GameObject & obj)
{
	float speed = 0.2f;
	Vector3 vec = Vector3::Up * speed;
	Quaternion q = obj.GetTransform().WorldDir();
	Vector3 accel = Vector3::Transform(vec, q);
	obj.GetTransform().WorldAccel(accel);
}
