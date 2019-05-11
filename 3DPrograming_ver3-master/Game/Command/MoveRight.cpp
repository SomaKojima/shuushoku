#include "../../pch.h"
#include "MoveRight.h"

using namespace std;
using namespace DirectX;
using namespace DirectX::SimpleMath;

/// <summary>
/// �R���X�g���N�^
/// </summary>
MoveRight::MoveRight()
{
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
MoveRight::~MoveRight()
{
}

/// <summary>
/// ���s
/// </summary>
/// <param name="obj"></param>
void MoveRight::Excute(GameObject & obj)
{
	float speed = 0.005f;
	Vector3 vec = Vector3::Left * speed;
	Quaternion dir = obj.GetTransform().WorldDir();
	Vector3 accel = obj.GetTransform().WorldAccel() + Vector3::Transform(vec, dir);
	obj.GetTransform().WorldAccel(accel);
}
