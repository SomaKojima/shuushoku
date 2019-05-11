#include "../../pch.h"
#include "MoveBackward.h"

using namespace std;
using namespace DirectX;
using namespace DirectX::SimpleMath;

/// <summary>
/// コンストラクタ
/// </summary>
MoveBackward::MoveBackward()
{
}

/// <summary>
/// デストラクタ
/// </summary>
MoveBackward::~MoveBackward()
{
}

/// <summary>
/// 実行
/// </summary>
/// <param name="obj"></param>
void MoveBackward::Excute(GameObject & obj)
{
	float speed = 0.005f;
	Vector3 vec = Vector3::Forward *speed;
	Quaternion dir = obj.GetTransform().WorldDir();
	Vector3 accel = obj.GetTransform().WorldAccel() + Vector3::Transform(vec, dir);
	obj.GetTransform().WorldAccel(accel);
}
