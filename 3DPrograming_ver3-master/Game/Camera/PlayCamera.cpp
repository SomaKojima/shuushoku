#include "../../pch.h"
#include "PlayCamera.h"
#include "Mouse.h"
#include "../Object/GameObject.h"
#include "CameraManager.h"
#include "../MouseCursor/MouseCurosrManager.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

PlayCamera::PlayCamera(GameObject* player)
	:
	m_target(player),
	m_x(0),
	m_y(0)
{
}

void PlayCamera::Initialize()
{

}

void PlayCamera::Update(float elapsedTime)
{
	/*Vector3 eyeVec = Vector3::Transform(Vector3(0.0f, 3.0f, -5.0f), m_target->GetTransform().WorldDir());
	Vector3 eyePos = m_target->GetTransform().WorldMatrix().Translation() + eyeVec;

	SetPositionTarget(eyePos, m_target->GetTransform().WorldMatrix().Translation());*/


	// ----- ウィンドウの情報が取得できない場合 -----
	if (!GetActiveWindow() || MouseCursorManager::GetInstace().GetIsMove())
	{
		return;
	}

	// ----- ウィンドウの長方形(Rectangle)の情報を取得する
	RECT wRect;
	GetWindowRect(GetActiveWindow(), &wRect);
	int width = (wRect.right - wRect.left) / 2;
	int height = (wRect.bottom - wRect.top) / 2;

	// ----- ウィンドウの中心座標を取得する -----
	int centralX = wRect.left + width;
	int centralY = wRect.top + height;

	// ----- マウスの座標を取得する -----
	POINT p;
	GetCursorPos(&p);

	// ----- マウスの移動量を取得する -----
	Vector2 mouseVec = Vector2(p.x - centralX, p.y - centralY);
	mouseVec *= 0.1f;


	// ----- 回転を更新 -----
	m_x += XMConvertToRadians(mouseVec.x);
	m_y += XMConvertToRadians(mouseVec.y);

	if (m_y > XMConvertToRadians(90.0f))
	{
		m_y = XMConvertToRadians(90.0f);
	}
	else if (m_y < -XMConvertToRadians(90.0f))
	{
		m_y = -XMConvertToRadians(90.0f);
	}

	Quaternion q = Quaternion::CreateFromYawPitchRoll(-m_x, m_y, 0.0f);

	Quaternion dir = Quaternion::Identity;
	Vector3 upDir = Vector3::Transform(Vector3::Up, m_target->GetTransform().WorldDir());
	float degree = mouseVec.x;
	Quaternion cameraDir = Quaternion::Identity;
	q = Quaternion::CreateFromYawPitchRoll(0.0f, m_y, 0.0f);
	if (mouseVec.x != 0)
	{
		dir = Quaternion::CreateFromAxisAngle(upDir, -XMConvertToRadians(degree));
	}

	// プレイヤーの向きを変える
	dir = m_target->GetTransform().WorldDir() * dir;
	m_target->GetTransform().WorldDir(dir);

	// カメラの向きを設定する
	cameraDir = q * m_target->GetTransform().WorldDir();

	// ----- カメラの座標を求める -----
	Vector3 eyeVec = Vector3::Transform(Vector3(0.0f, 0.0f, -10.0f), cameraDir) +
		Vector3::Transform(Vector3(0.0f, 2.0f * cos(m_y), 2.0f * sin(m_y)), m_target->GetTransform().WorldDir());
	Vector3 eyePos = m_target->GetTransform().WorldPos() + eyeVec;
	Vector3 target = m_target->GetTransform().WorldPos() + Vector3::Transform(Vector3(0.0f, 0.0f, 10.0f), cameraDir);

	SetPositionTarget(eyePos, target);


	// カメラ管理のビューを更新する
	CameraManager& cameraManager = CameraManager::GetInstace();
	cameraManager.SetView(Matrix::CreateLookAt(GetEyePosition(), GetTargetPosition(), GetUp()));
}

DirectX::SimpleMath::Vector3 PlayCamera::GetUp()
{
	Vector3 up = Vector3::Transform(Vector3::Up, m_target->GetTransform().WorldDir());
	return up;
}
