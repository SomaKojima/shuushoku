#include "../../pch.h"
#include "Accel.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

/// <summary>
/// �R���X�g���N�^
/// </summary>
Accel::Accel()
{
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
Accel::~Accel()
{
}

/// <summary>
/// ���s�֐�
/// </summary>
/// <param name="obj"></param>
void Accel::Excute(GameObject & obj)
{
	float speed = 0.2f;
	Vector3 vec = Vector3::Backward * speed;
	Quaternion q = obj.GetTransform().WorldDir();
	Vector3 accel = Vector3::Transform(vec, q);
	obj.GetTransform().WorldAccel(accel);
}
