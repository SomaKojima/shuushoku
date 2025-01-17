#include "../../../pch.h"
#include "Car.h"

#include "../../Component/Render/RenderThreeDimension.h"
#include "../../Component/Physics/Gravity.h"
#include "../../Component/Physics/Friction.h"
#include "../../Component/Controller/PlayerController.h"
#include "../../Component/Object/PositionControl.h"

#include "../../Collision/CollisionSphere.h"

#include"../../Data/Model/ModelData.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

/// <summary>
/// コンストラクタ
/// </summary>
Car::Car()
{
}

/// <summary>
/// デストラクタ
/// </summary>
Car::~Car()
{
}

/// <summary>
/// 生成関数
/// </summary>
void Car::Instance()
{
	// モデル取得
	ModelData& modelData = CarBodyModel::GetInstace();
	// 3Dモデル描画のコンポーネントを作成
	Component* renderThreeDimention = new RenderThreeDimention(modelData.GetModel(), RenderThreeDimention::Type::Nomal);
	AddComponent(renderThreeDimention);
	// 球の当たり判定を作成
	Component* collisionSphere = new CollisionSphere(Vector3::Zero,1.5f);
	AddComponent(collisionSphere);
	// 重力のコンポーネントを作成
	Component* gravity = new Gravity();
	AddComponent(gravity);
	// 摩擦のコンポーネントを作成
	Component* friction = new Friction();
	AddComponent(friction);
	// 操作のコンポーネントを作成
	Component* playerController = new PlayerController();
	AddComponent(playerController);
	// 姿勢制御のコンポーネントを作成
	PositionControl* positionControl = new PositionControl();
	AddComponent(positionControl);
}
