/// <summary>
/// SphereCollisionComponent.cpp
/// 
/// 制作日:2018/7/4
/// 制作者:小嶋 颯天
/// </summary>

/// <summary>
/// ヘッダのインクルード
/// </summary>
#include "../../pch.h"
#include "CollisionSphere.h"
#include "../SubGame.h"
//#include "BoxCollisionComponent.h"

/// <summary>
/// 名前空間
/// </summary>
using namespace DirectX;
using namespace DirectX::SimpleMath;

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="center">中心座標</param>
/// <param name="radius">半径</param>
CollisionSphere::CollisionSphere(DirectX::SimpleMath::Vector3 center, float radius)
	:
	CollisionComponent(Collision::SHAPE_TYPE::SHAPE_TYPE_SPHERE),
	m_center(center),
	m_radius(radius),
	m_obj(nullptr)
{
	m_sphere.radius = radius;
}

/// <summary>
/// デストラクタ
/// </summary>
CollisionSphere::~CollisionSphere()
{

}

void CollisionSphere::Update(float elapsedTime)
{
	CollisionComponent::Update(elapsedTime);
}

void CollisionSphere::LateUpdate(float elapsedTime)
{
	m_sphere.center = Vector3::Transform(m_center, (m_gameObject->GetTransform().WorldMatrix()));
}

/// <summary>
/// 描画
/// </summary>
/// <param name="entity">実体</param>
/// <param name="game">ゲーム</param>
void CollisionSphere::Render()
{
	Matrix world = m_gameObject->GetTransform().WorldMatrix() * Matrix::CreateTranslation(m_center);
	if (m_obj == nullptr)
	{
		// デバッグ用当たり判定モデルの作成
		m_obj = std::make_unique<DebugSphere>(SubGame::GetInstace().GetGame()->GetDevice(), m_center, m_radius);
	}
	else
	{
		Game* game = SubGame::GetInstace().GetGame();
		m_obj->Draw(game->GetContext(), *game->GetStates(), world, game->GetView(), game->GetProjection());
	}
}

/// <summary>
/// 終了
/// </summary>
/// <param name="entity">実体</param>
void CollisionSphere::Finalize()
{
	m_obj.reset();
}

void CollisionSphere::OnTriangleCollision(GameObject & obj, const Collision::Triangle & triangle, DirectX::SimpleMath::Vector3 & hitPos)
{
	// 壁刷り
	HitBack(triangle, hitPos);
}

bool CollisionSphere::SphereCollision(GameObject& obj, const Collision::Sphere & sphere, DirectX::SimpleMath::Vector3& hitPos)
{
	if (Collision::HitCheck(m_sphere, sphere, &hitPos))
	{
		// 自身の処理
		for (auto ite = m_gameObject->GetComponentList().begin(); ite != m_gameObject->GetComponentList().end(); ite++)
		{
			(*ite)->OnSphereCollision(obj, sphere, hitPos);
		}
		// 相手の処理
		for (auto ite = obj.GetComponentList().begin(); ite != obj.GetComponentList().end(); ite++)
		{
			(*ite)->OnSphereCollision(*m_gameObject, m_sphere, hitPos);
		}
		return true;
	}
	return false;
}

bool CollisionSphere::TriangleCollision(GameObject& obj, const Collision::Triangle & triangle, DirectX::SimpleMath::Vector3& hitPos)
{
	if (Collision::HitCheck(m_sphere, triangle, &hitPos))
	{
		// 自身の処理
		for (auto ite = m_gameObject->GetComponentList().begin(); ite != m_gameObject->GetComponentList().end(); ite++)
		{
			(*ite)->OnTriangleCollision(obj, triangle, hitPos);
		}
		// 相手の処理
		for (auto ite = obj.GetComponentList().begin(); ite != obj.GetComponentList().end(); ite++)
		{
			(*ite)->OnSphereCollision(*m_gameObject, m_sphere, hitPos);
		}
		return true;
	}
	return false;
}



void CollisionSphere::HitBack(const Collision::Triangle & triangle, DirectX::SimpleMath::Vector3 & hitPos)
{
	// 速度で壁刷りを行う
	Vector3 w_vec_vel = WallCulc(triangle, hitPos, m_gameObject->GetTransform().WorldVel());
	m_gameObject->GetTransform().WorldVel(w_vec_vel);


	// 座標の更新
	Vector3 pos = m_gameObject->GetTransform().WorldPos();

	Vector3 normal(triangle.plane.a, triangle.plane.b, triangle.plane.c);
	Vector3 hit;
	Collision::HitCheck_Sphere_Plane(m_sphere, triangle.plane, &hit);
	pos = hit + normal * m_radius;
	m_gameObject->GetTransform().WorldPos(pos);

	// 加速度を壁刷りを行った速度にする
	Vector3 w_vec_accel = WallCulc(triangle, hitPos, m_gameObject->GetTransform().WorldAccel());
	m_gameObject->GetTransform().WorldAccel(w_vec_accel);
}


/// <summary>
/// 壁刷りの計算
/// </summary>
/// <param name="triangle"></param>
/// <param name="hitPos"></param>
/// <param name="vel"></param>
/// <returns></returns>
Vector3 CollisionSphere::WallCulc(const Collision::Triangle& triangle, Vector3 & hitPos, SimpleMath::Vector3 vel)
{
	// 速度を取得
	Vector3 vec = vel;

	// 面の法線
	Vector3 normal(triangle.plane.a, triangle.plane.b, triangle.plane.c);

	float l = vec.Dot(normal);

	if(l < 0.0f)
	{
		return vec - l * normal;
	}
	return vec;
}

