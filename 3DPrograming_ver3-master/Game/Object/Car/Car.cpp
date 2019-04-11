#include "../../../pch.h"
#include "Car.h"

#include "../../Component/Render/RenderThreeDimension.h"

#include"../../Data/Model/ModelData.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
Car::Car()
{
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
Car::~Car()
{
}

/// <summary>
/// �����֐�
/// </summary>
void Car::Instance()
{
	// ���f���擾
	ModelData& modelData = CarBodyModel::GetInstace();
	// 3D���f���`��̃R���|�[�l���g���쐬
	Component* renderThreeDimention = new RenderThreeDimention(modelData.GetModel(), RenderThreeDimention::Type::Nomal);
	AddComponent(renderThreeDimention);
}
