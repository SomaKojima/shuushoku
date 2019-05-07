/// <summary>
/// �C���N���[�h
/// </summary>
#include <locale>
#include <codecvt>
#include <string>
#include "pch.h"
#include "DebugString.h"


/// <summary>
/// ���O���
/// </summary>
using namespace std;
using namespace DirectX;
using namespace DirectX::SimpleMath;

/// <summary>
/// �R���X�g���N�^
/// </summary>
DebugString::DebugString()
{
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
DebugString::~DebugString()
{
}

/// <summary>
/// ������
/// </summary>
/// <param name="device"></param>
/// <param name="context"></param>
void DebugString::Initialize(DirectX::SpriteBatch* sprites, DirectX::SpriteFont* font)
{
	m_sprites = sprites;
	m_font = font;
}

/// <summary>
/// �X�V
/// </summary>
/// <param name="timer"></param>
void DebugString::Update(DX::StepTimer const & timer)
{
	// 1�b���ƂɃf�o�b�O�e�L�X�g��1�s����
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
/// �`��
/// </summary>
/// <param name="game"></param>
void DebugString::Render()
{
	Vector2 pos = Vector2::Zero;
	for (auto ite = m_strings.begin(); ite != m_strings.end(); ite++)
	{

		//string����wchar_t�^�֕ϊ�
		std::wstring_convert
			<std::codecvt_utf8<wchar_t>, wchar_t> cv;
		std::wstring wsnum = cv.from_bytes((*ite));

		m_font->DrawString(m_sprites, wsnum.c_str(), pos, Colors::Red, 0.0f, Vector2::Zero, 1.0f, SpriteEffects_None, 1.0f);
		pos.y += 32;
	}
}

/// <summary>
/// �e�L�X�g�̒ǉ�
/// </summary>
/// <param name="str"></param>
void DebugString::DebugText(std::string str)
{
	if (m_strings.size() >= MAX)
	{
		// MAX��萔���������Ȃ�܂Ō��炷
		while (m_strings.size() >= MAX)
		{
			m_strings.erase(m_strings.begin());
		}
	}
	m_strings.push_back(str);
}

/// <summary>
/// Int��String�ɕϊ�
/// </summary>
/// <param name="num"></param>
/// <returns></returns>
std::string DebugString::ToS(int num)
{
	return std::to_string(num);
}

/// <summary>
/// Vector3��String�ɕϊ�
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
