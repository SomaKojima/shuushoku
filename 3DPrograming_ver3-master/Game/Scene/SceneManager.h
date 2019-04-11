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

	// �����֐�
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

	// ����������
	void Initialize();
	// �X�V����
	void Update(float elapsedTime);
	// �`�揈��
	void Render();
	// �I������
	void Finalize();

	// �V�[����ID��ς���
	void ChangeSceneID(SceneID sceneid) { m_changeSceneID = sceneid; }

	// �V�[����ς��鏈��
	void ChangeScene();

private:
	// ���݂̃V�[��ID
	SceneID m_currentSceneID;
	// �ς���Ƃ��Ɏg�p���鎟�̃V�[����ID
	SceneID m_changeSceneID;
	// ���݂̃V�[��
	Scene* m_currentScene;
};
