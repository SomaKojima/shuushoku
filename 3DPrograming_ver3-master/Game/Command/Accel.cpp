#include "../../pch.h"
#include "Accel.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

/// <summary>
/// コンストラクタ
/// </summary>
Accel::Accel()
{
}

/// <summary>
/// デストラクタ
/// </summary>
Accel::~Accel()
{
}

/// <summary>
/// 実行関数
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
