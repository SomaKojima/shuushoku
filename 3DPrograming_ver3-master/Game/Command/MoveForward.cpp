#include "../../pch.h"
#include "MoveForward.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

/// <summary>
/// コンストラクタ
/// </summary>
MoveForward::MoveForward()
{
}

/// <summary>
/// デストラクタ
/// </summary>
MoveForward::~MoveForward()
{
}

/// <summary>
/// 実行関数
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
