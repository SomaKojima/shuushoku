#pragma once

class Game;

class SubGame
{
public:
	//　コンストラクタ
	SubGame(Game* game);
	~SubGame();
public:
	// 初期化処理
	void Initialize();
	// 更新処理
	void Update(float elapsedTime);
	// 描画処理
	void Renderer();
	// 終了処理
	void Finalize();
private:
	Game* m_game;
};