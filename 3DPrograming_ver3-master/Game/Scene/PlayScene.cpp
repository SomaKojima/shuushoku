#include "../../pch.h"
#include "PlayScene.h"
#include "../Object/Car/Car.h"

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
	GameObject* obj = new Car();
	obj->Instance();
	m_gameObjectList.Add(obj);
}
