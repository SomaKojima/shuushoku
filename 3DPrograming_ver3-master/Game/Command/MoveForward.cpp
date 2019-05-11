#include "../../pch.h"
#include "MoveForward.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

/// <summary>
/// �R���X�g���N�^
/// </summary>
MoveForward::MoveForward()
{
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
MoveForward::~MoveForward()
{
}

/// <summary>
/// ���s�֐�
/// </summary>
/// <param name="obj"></param>
void MoveForward::Excute(GameObject & obj)
{
	float speed = 0.005f;
	Vector3 vec = Vector3::Backward * speed;
	Quaternion dir = obj.GetTransform().WorldDir();
	Vector3 accel = obj.GetTransform().WorldAccel() + Vector3::Transform(vec, dir);
	obj.GetTransform().WorldAccel(accel);
}
