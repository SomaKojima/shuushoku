#pragma once

class Game;

class SubGame
{
public:
	//�@�R���X�g���N�^
	SubGame(Game* game);
	~SubGame();
public:
	// ����������
	void Initialize();
	// �X�V����
	void Update(float elapsedTime);
	// �`�揈��
	void Renderer();
	// �I������
	void Finalize();
private:
	Game* m_game;
};