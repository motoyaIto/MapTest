//
//�f�o�b�N�p�J����
//
//Motoya Ito
//2017/10/16
//�Q�l����:�w�Z�z�z�̃v���W�F�N�g
#include "DebugCamera.h"

#include <Mouse.h>

DebugCamera::DebugCamera(int width, int height)
	: Camera(width, height)
	, m_nowAngle(Vector2::Zero)
	, m_afterAngle(Vector2::Zero)
	, m_drag(Vector2::Zero)
	, m_relativeScale(Vector2(1.0f / (float)width, 1.0f / (float)height))
	, m_scrollWheelValue(0)
{
	
	
}

DebugCamera::~DebugCamera()
{
}

/// <summary>
/// �X�V
/// </summary>
void DebugCamera::Update()
{
	// �}�E�X�����擾
	
}
