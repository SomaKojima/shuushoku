/// <summary>
/// SphereCollisionComponent.cpp
/// 
/// �����:2018/7/4
/// �����:���� �D�V
/// </summary>

/// <summary>
/// �w�b�_�̃C���N���[�h
/// </summary>
#include "../../pch.h"
#include "CollisionSphere.h"
#include "../SubGame.h"
//#include "BoxCollisionComponent.h"

/// <summary>
/// ���O���
/// </summary>
using namespace DirectX;
using namespace DirectX::SimpleMath;

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="center">���S���W</param>
/// <param name="radius">���a</param>
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
/// �f�X�g���N�^
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
/// �`��
/// </summary>
/// <param name="entity">����</param>
/// <param name="game">�Q�[��</param>
void CollisionSphere::Render()
{
	Matrix world = m_gameObject->GetTransform().WorldMatrix() * Matrix::CreateTranslation(m_center);
	if (m_obj == nullptr)
	{
		// �f�o�b�O�p�����蔻�胂�f���̍쐬
		m_obj = std::make_unique<DebugSphere>(SubGame::GetInstace().GetGame()->GetDevice(), m_center, m_radius);
	}
	else
	{
		Game* game = SubGame::GetInstace().GetGame();
		m_obj->Draw(game->GetContext(), *game->GetStates(), world, game->GetView(), game->GetProjection());
	}
}

/// <summary>
/// �I��
/// </summary>
/// <param name="entity">����</param>
void CollisionSphere::Finalize()
{
	m_obj.reset();
}

void CollisionSphere::OnTriangleCollision(GameObject & obj, const Collision::Triangle & triangle, DirectX::SimpleMath::Vector3 & hitPos)
{
	// �Ǎ���
	HitBack(triangle, hitPos);
}

bool CollisionSphere::SphereCollision(const Collision::Sphere & sphere, DirectX::SimpleMath::Vector3& hitPos)
{
	if (Collision::HitCheck(m_sphere, sphere, &hitPos))
	{
		return true;
	}
	return false;
}

bool CollisionSphere::TriangleCollision(const Collision::Triangle & triangle, DirectX::SimpleMath::Vector3& hitPos)
{
	if (Collision::HitCheck(m_sphere, triangle, &hitPos))
	{
		return true;
	}
	return false;
}



void CollisionSphere::HitBack(const Collision::Triangle & triangle, DirectX::SimpleMath::Vector3 & hitPos)
{
	// ���x�ŕǍ�����s��
	 Vector3 w_vec_vel = WallCulc(triangle, hitPos, m_gameObject->GetTransform().WorldVel());
	 m_gameObject->GetTransform().WorldVel(w_vec_vel);


	// ���W�̍X�V
	//Vector3 pos = m_gameObject->GetTransform().WorldPos();
	//Vector3 vec = pos - hitPos;
	//vec.Normalize();
	////vec = Vector3(triangle.plane.a, triangle.plane.b, triangle.plane.c);
	//Vector3 _hit_pos = hitPos;
	////Collision::HitCheck_Sphere_Plane(m_sphere, triangle.plane, &_hit_pos);
	//pos = pos + vec * m_radius;
	//m_gameObject->GetTransform().WorldPos(pos);

	// �����x��Ǎ�����s�������x�ɂ���
	Vector3 w_vec_accel = WallCulc(triangle, hitPos, m_gameObject->GetTransform().WorldAccel());
	m_gameObject->GetTransform().WorldAccel(w_vec_accel);
}


/// <summary>
/// �Ǎ���̌v�Z
/// </summary>
/// <param name="triangle"></param>
/// <param name="hitPos"></param>
/// <param name="vel"></param>
/// <returns></returns>
Vector3& CollisionSphere::WallCulc(const Collision::Triangle& triangle, Vector3 & hitPos, SimpleMath::Vector3 vel)
{
	// ���x���擾
	Vector3 vec = vel;

	// �ʂ̖@��
	Vector3 normal(triangle.plane.a, triangle.plane.b, triangle.plane.c);

	float l = vec.Dot(normal);
	Vector3 w_vec = vec - l * normal;

	// ���̌����ɍ��킹��
	return w_vec;
}

