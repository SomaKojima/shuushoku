#include "../../../pch.h"
#include "Car.h"

#include "../../Component/Render/RenderThreeDimension.h"

#include"../../Data/Model/ModelData.h"

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
}
