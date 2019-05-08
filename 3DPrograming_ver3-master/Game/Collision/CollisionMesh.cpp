
#include <fstream>
#include "../../pch.h"
#include "CollisionMesh.h"
#include "../SubGame.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

CollisionMesh::CollisionMesh(wchar_t * file)
	:
	CollisionComponent(Collision::SHAPE_TYPE::SHAPE_TYPE_MESH),
	m_file(file),
	m_isFile(false)
{
	// obj形式のファイル読み込み
	std::vector<Vector3> vertexes;
	std::vector<int> indexes;
	std::ifstream ifs(file);
	if (!ifs)
	{
		ifs.close();
		return;
	}
	m_isFile = true;
	std::string str;
	while (getline(ifs, str))
	{
		// 頂点
		if (str[0] == 'v')
		{
			Vector3 val;
			sscanf_s(str.data(), "v  %f %f %f", &val.x, &val.y, &val.z);
			vertexes.push_back(val);
		}
		// インデックス
		if (str[0] == 'f')
		{
			int a, b, c;
			sscanf_s(str.data(), "f %d %d %d", &a, &b, &c);
			// 三角形の頂点インデックス番号が同じ物を含む場合は無視する
			if (a != b && a != c && b != c)
			{
				indexes.push_back(a - 1);
				indexes.push_back(c - 1);
				indexes.push_back(b - 1);
			}
		}
	}
	ifs.close();

	for (size_t i = 0; i < indexes.size() / 3; i++)
	{
		Collision::Triangle triangle;
		triangle.Set_Triangle(vertexes[indexes[i * 3 + 2]], vertexes[indexes[i * 3 + 1]], vertexes[indexes[i * 3]]);
		m_triangles.push_back(Collision::Triangle(triangle));
	}
}

CollisionMesh::~CollisionMesh()
{
}

void CollisionMesh::Update(float elapsedTime)
{
	CollisionComponent::Update(elapsedTime);
}

void CollisionMesh::LateUpdate(float elapsedTime)
{
}

void CollisionMesh::Render()
{
	if (m_obj == nullptr && m_isFile)
	{
		// デバッグ用当たり判定モデルの作成
		m_obj = std::make_unique<DebugMesh>(SubGame::GetInstace().GetGame()->GetDevice(), m_file);
	}
	else if(m_obj)
	{
		Game* game = SubGame::GetInstace().GetGame();
		m_obj->DrawCollision(game->GetContext(), game->GetView(), game->GetProjection());
	}
}

void CollisionMesh::Finalize()
{
	m_obj.reset();
}

bool CollisionMesh::SphereCollision(GameObject& obj, const Collision::Sphere& sphere, DirectX::SimpleMath::Vector3& hitPos)
{
	for (auto ite = m_triangles.begin(); ite != m_triangles.end(); ite++)
	{
		if (Collision::HitCheck((*ite), sphere, &hitPos))
		{
			// 自身の処理
			for (auto ite2 = m_gameObject->GetComponentList().begin(); ite2 != m_gameObject->GetComponentList().end(); ite2++)
			{
				(*ite2)->OnSphereCollision(obj, sphere, hitPos);
			}
			// 相手の処理
			for (auto ite2 = obj.GetComponentList().begin(); ite2 != obj.GetComponentList().end(); ite2++)
			{
				(*ite2)->OnTriangleCollision(*m_gameObject, (*ite), hitPos);
			}
			return true;
		}
	}
	return false;
}

bool CollisionMesh::TriangleCollision(GameObject& obj, const Collision::Triangle& triangle, DirectX::SimpleMath::Vector3& hitPos)
{
	for (auto ite = m_triangles.begin(); ite != m_triangles.end(); ite++)
	{
		if (Collision::HitCheck((*ite), triangle, &hitPos))
		{
			// 自身の処理
			for (auto ite2 = m_gameObject->GetComponentList().begin(); ite2 != m_gameObject->GetComponentList().end(); ite2++)
			{
				(*ite2)->OnTriangleCollision(obj, triangle, hitPos);
			}
			// 相手の処理
			for (auto ite2 = obj.GetComponentList().begin(); ite2 != obj.GetComponentList().end(); ite2++)
			{
				(*ite2)->OnTriangleCollision(*m_gameObject, (*ite), hitPos);
			}
			return true;
		}
	}
	return false;
}
