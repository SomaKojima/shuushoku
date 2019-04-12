#include "../../pch.h"
#include "PlayScene.h"
#include "../Object/GameObject.h"
#include "../Object/Car/Car.h"
#include "../Camera/Camera.h"

/// <summary>
/// コンストラクタ
/// </summary>
PlayScene::PlayScene()
{
}

/// <summary>
/// デストラクタ
/// </summary>
PlayScene::~PlayScene()
{
}

/// <summary>
/// 生成関数
/// </summary>
void PlayScene::Instance()
{
	// 車の作成
	GameObject* car = new Car();
	car->Instance();
	m_gameObjectList.Add(car);

	// カメラの作成
	GameObject* camera = new Camera(car);
	camera->Instance();
	m_gameObjectList.Add(camera);
}
