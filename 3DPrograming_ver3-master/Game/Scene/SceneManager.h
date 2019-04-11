#pragma once

#include "../../StepTimer.h"
#include "../Utility/Singleton.h"
#include "../Object/GameObjectList.h"

class Game;

class Scene
{
public:
	Scene() {}
	virtual ~Scene() {}

	// 生成関数
	virtual void Instance() = 0;

	GameObjectList& GetGameObjectList() { return m_gameObjectList; }
private:
	GameObjectList m_gameObjectList;
};

class SceneManager : public Singleton<SceneManager>
{
public:
	enum SceneID
	{
		Title,
		Play,

		Max
	};

public:
	SceneManager();
	~SceneManager();

	// 初期化処理
	void Initialize();
	// 更新処理
	void Update(float elapsedTime);
	// 描画処理
	void Render();
	// 終了処理
	void Finalize();

	// シーンのIDを変える
	void ChangeSceneID(SceneID sceneid) { m_changeSceneID = sceneid; }

	// シーンを変える処理
	void ChangeScene();

private:
	// 現在のシーンID
	SceneID m_currentSceneID;
	// 変えるときに使用する次のシーンのID
	SceneID m_changeSceneID;
	// 現在のシーン
	Scene* m_currentScene;
};
