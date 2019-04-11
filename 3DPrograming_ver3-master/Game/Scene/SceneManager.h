#pragma once

#include "../../StepTimer.h"
#include "../Utility/Singleton.h"

class Game;

class Scene
{
public:
	Scene() {}
	virtual ~Scene() {}

	// ������
	virtual void Initialize() = 0;
	// �X�V
	virtual void Update() = 0;
	// �`��
	virtual void Renderer() = 0;
	// �I��
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

	// �X�V����
	void Update(DX::StepTimer const& timer);
	// �`�揈��
	void Render();
	// �I������
	void Finalize();

	// �V�[����ID��ς���
	void ChangeSceneID(SceneID sceneid) { m_changeSceneID = sceneid; }

	// �V�[����ς��鏈��
	void ChangeScene();
private:
	// ����������
	void Initialize();

private:
	// ���݂̃V�[��ID
	SceneID m_currentSceneID;
	// �ς���Ƃ��Ɏg�p���鎟�̃V�[����ID
	SceneID m_changeSceneID;
	// ���݂̃V�[��
	Scene* m_currentScene;
};
