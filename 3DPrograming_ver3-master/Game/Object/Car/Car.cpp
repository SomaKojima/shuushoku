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
	// ���̓����蔻����쐬
	Component* collisionSphere = new CollisionSphere(Vector3::Zero,1.5f);
	AddComponent(collisionSphere);
	// �d�͂̃R���|�[�l���g���쐬
	Component* gravity = new Gravity();
	AddComponent(gravity);
	// ���C�̃R���|�[�l���g���쐬
	Component* friction = new Friction();
	AddComponent(friction);
	// ����̃R���|�[�l���g���쐬
	Component* playerController = new PlayerController();
	AddComponent(playerController);
	// �p������̃R���|�[�l���g���쐬
	PositionControl* positionControl = new PositionControl();
	AddComponent(positionControl);
}
