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

bool CollisionSphere::SphereCollision(GameObject& obj, const Collision::Sphere & sphere, DirectX::SimpleMath::Vector3& hitPos)
{
	if (Collision::HitCheck(m_sphere, sphere, &hitPos))
	{
		// ���g�̏���
		for (auto ite = m_gameObject->GetComponentList().begin(); ite != m_gameObject->GetComponentList().end(); ite++)
		{
			(*ite)->OnSphereCollision(obj, sphere, hitPos);
		}
		// ����̏���
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
		// ���g�̏���
		for (auto ite = m_gameObject->GetComponentList().begin(); ite != m_gameObject->GetComponentList().end(); ite++)
		{
			(*ite)->OnTriangleCollision(obj, triangle, hitPos);
		}
		// ����̏���
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
	// ���x�ŕǍ�����s��
	Vector3 w_vec_vel = WallCulc(triangle, hitPos, m_gameObject->GetTransform().WorldVel());
	m_gameObject->GetTransform().WorldVel(w_vec_vel);


	// ���W�̍X�V
	Vector3 pos = m_gameObject->GetTransform().WorldPos();

	Vector3 normal(triangle.plane.a, triangle.plane.b, triangle.plane.c);
	pos = hitPos + normal * m_radius;
	m_gameObject->GetTransform().WorldPos(pos);

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
	Vector3 w_vec;
	if(l <= 0)
	{
		w_vec = vec - l * normal;
	}
	else
	{
		w_vec = vec;
	}

	// ���̌����ɍ��킹��
	return w_vec;
}

