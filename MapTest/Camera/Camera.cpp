//
//カメラの基底クラス
//
//Motoya Ito
//2017/10/16
#include "Camera.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

Camera::Camera(int width, int height)
	: m_proj(Matrix::Identity)
	, m_fovY(XMConvertToRadians(60.0f))
	, m_aspect((float)width / height)
	, m_nearclip(0.1f)
	, m_farclip(1000.0f)

	, m_view(Matrix::Identity)
	, m_eyepos(Vector3(0.0f, 6.0f, 10.0f))
	, m_refpos(Vector3(0.0f, 2.0f, 0.0f))
	, m_upvec(Vector3(0.0f, 1.0f, 0.0f))
{
}

Camera::~Camera()
{
}

void Camera::Update()
{
	//ビュー行列を作成
	m_view = Matrix::CreateLookAt(m_eyepos, m_refpos, m_upvec);

	//プロジェクション行列
	m_proj = Matrix::CreatePerspectiveFieldOfView(m_fovY, m_aspect, m_nearclip, m_farclip);
}
