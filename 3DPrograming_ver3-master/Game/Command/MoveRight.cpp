#include "../../pch.h"
#include "MoveRight.h"

using namespace std;
using namespace DirectX;
using namespace DirectX::SimpleMath;

/// <summary>
/// コンストラクタ
/// </summary>
MoveRight::MoveRight()
{
}

/// <summary>
/// デストラクタ
/// </summary>
MoveRight::~MoveRight()
{
}

/// <summary>
/// 実行
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
