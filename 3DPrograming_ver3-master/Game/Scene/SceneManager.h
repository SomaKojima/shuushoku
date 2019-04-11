#pragma once

#include "../../StepTimer.h"
#include "../Utility/Singleton.h"

class Game;

class Scene
{
public:
	Scene() {}
	virtual ~Scene() {}

	// 初期化
	virtual void Initialize() = 0;
	// 更新
	virtual void Update() = 0;
	// 描画
	virtual void Renderer() = 0;
	// 終了
	virtual void Finalize() = 0;
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

	// 更新処理
	void Update(DX::StepTimer const& timer);
	// 描画処理
	void Render();
	// 終了処理
	void Finalize();

	// シーンのIDを変える
	void ChangeSceneID(SceneID sceneid) { m_changeSceneID = sceneid; }

	// シーンを変える処理
	void ChangeScene();
private:
	// 初期化処理
	void Initialize();

private:
	// 現在のシーンID
	SceneID m_currentSceneID;
	// 変えるときに使用する次のシーンのID
	SceneID m_changeSceneID;
	// 現在のシーン
	Scene* m_currentScene;
};
