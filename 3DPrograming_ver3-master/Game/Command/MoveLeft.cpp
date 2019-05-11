#include "../../pch.h"
#include "MoveLeft.h"

using namespace std;
using namespace DirectX;
using namespace DirectX::SimpleMath;

/// <summary>
/// コンストラクタ
/// </summary>
MoveLeft::MoveLeft()
{
}

/// <summary>
/// デストラクタ
/// </summary>
MoveLeft::~MoveLeft()
{
}

/// <summary>
/// 実行
/// </summary>
/// <param name="obj"></param>
void MoveLeft::Excute(GameObject & obj)
{
	float speed = 0.005f;
	Vector3 vec = Vector3::Right * speed;
	Quaternion dir = obj.GetTransform().WorldDir();
	Vector3 accel = obj.GetTransform().WorldAccel() + Vector3::Transform(vec, dir);
	obj.GetTransform().WorldAccel(accel);
}
