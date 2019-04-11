#include "../../pch.h"
#include "PlayScene.h"
#include "../Object/Car/Car.h"

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
	GameObject* obj = new Car();
	obj->Instance();
	m_gameObjectList.Add(obj);
}
