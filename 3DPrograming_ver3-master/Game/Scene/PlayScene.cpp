#include "../../pch.h"
#include "PlayScene.h"
#include "../Object/GameObject.h"
#include "../Object/Car/Car.h"
#include "../Camera/Camera.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
PlayScene::PlayScene()
{
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
PlayScene::~PlayScene()
{
}

/// <summary>
/// �����֐�
/// </summary>
void PlayScene::Instance()
{
	// �Ԃ̍쐬
	GameObject* car = new Car();
	car->Instance();
	m_gameObjectList.Add(car);

	// �J�����̍쐬
	GameObject* camera = new Camera(car);
	camera->Instance();
	m_gameObjectList.Add(camera);
}
