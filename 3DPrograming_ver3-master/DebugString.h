#pragma once

// インクルード
#include "Game\Utility\Singleton.h"
#include <list>
#include "StepTimer.h"

// 文字のデバッグクラス
class DebugString : public Singleton<DebugString>
{
public:
	static const int MAX = 10;
public:
	DebugString();
	~DebugString();

public:
	void Initialize(DirectX::SpriteBatch* sprites, DirectX::SpriteFont* font);
	void Update(DX::StepTimer const& timer);
	void Render();

	void DebugText(std::string str);
	std::string ToS(int num);
	std::string ToS(DirectX::SimpleMath::Vector3 vec);

private:
	// スプライトバッチ
	DirectX::SpriteBatch* m_sprites;
	// スプライトフォント
	DirectX::SpriteFont* m_font;

	std::list<std::string> m_strings;
};