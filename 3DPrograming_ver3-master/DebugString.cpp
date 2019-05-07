/// <summary>
/// インクルード
/// </summary>
#include <locale>
#include <codecvt>
#include <string>
#include "pch.h"
#include "DebugString.h"


/// <summary>
/// 名前空間
/// </summary>
using namespace std;
using namespace DirectX;
using namespace DirectX::SimpleMath;

/// <summary>
/// コンストラクタ
/// </summary>
DebugString::DebugString()
{
}

/// <summary>
/// デストラクタ
/// </summary>
DebugString::~DebugString()
{
}

/// <summary>
/// 初期化
/// </summary>
/// <param name="device"></param>
/// <param name="context"></param>
void DebugString::Initialize(DirectX::SpriteBatch* sprites, DirectX::SpriteFont* font)
{
	m_sprites = sprites;
	m_font = font;
}

/// <summary>
/// 更新
/// </summary>
/// <param name="timer"></param>
void DebugString::Update(DX::StepTimer const & timer)
{
	// 1秒ごとにデバッグテキストを1行消す
	static int second = 0;
	if ((int)(timer.GetTotalSeconds()) != second)
	{
		second = (int)(timer.GetTotalSeconds());
		if (m_strings.size() != 0)
		{
			m_strings.erase(m_strings.begin());
		}
	}
}

/// <summary>
/// 描画
/// </summary>
/// <param name="game"></param>
void DebugString::Render()
{
	Vector2 pos = Vector2::Zero;
	for (auto ite = m_strings.begin(); ite != m_strings.end(); ite++)
	{

		//stringからwchar_t型へ変換
		std::wstring_convert
			<std::codecvt_utf8<wchar_t>, wchar_t> cv;
		std::wstring wsnum = cv.from_bytes((*ite));

		m_font->DrawString(m_sprites, wsnum.c_str(), pos, Colors::Red, 0.0f, Vector2::Zero, 1.0f, SpriteEffects_None, 1.0f);
		pos.y += 32;
	}
}

/// <summary>
/// テキストの追加
/// </summary>
/// <param name="str"></param>
void DebugString::DebugText(std::string str)
{
	if (m_strings.size() >= MAX)
	{
		// MAXより数が小さくなるまで減らす
		while (m_strings.size() >= MAX)
		{
			m_strings.erase(m_strings.begin());
		}
	}
	m_strings.push_back(str);
}

/// <summary>
/// IntをStringに変換
/// </summary>
/// <param name="num"></param>
/// <returns></returns>
std::string DebugString::ToS(int num)
{
	return std::to_string(num);
}

/// <summary>
/// Vector3をStringに変換
/// </summary>
/// <param name="vec"></param>
/// <returns></returns>
std::string DebugString::ToS(Vector3 vec)
{
	string x = std::to_string(vec.x);
	string y = std::to_string(vec.y);
	string z = std::to_string(vec.z);
	return "(" + x + "," + y + "," + z + ")";
}
