//
//�f�o�b�N�p�J����
//
//Motoya Ito
//2017/10/16
//�Q�l����:�w�Z�z�z�̃v���W�F�N�g
#include "DebugCamera.h"

#include <Mouse.h>

#include "..//..//Mouse//MouseUtil.h"

//�ÓI�ϐ��̎���
const float DebugCamera::DEFAULT_CAMERA_DISTANCE = 5.0f;

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="width">��ʂ̉��̃T�C�Y</param>
/// <param name="height">��ʂ̏c�̃T�C�Y</param>
DebugCamera::DebugCamera(int width, int height)
	: Camera(width, height)
	, m_nowAngle(Vector2::Zero)
	, m_afterAngle(Vector2::Zero)
	, m_drag(Vector2::Zero)
	, m_relativeScale(Vector2(1.0f / (float)width, 1.0f / (float)height))
	, m_scrollWheelValue(0)
{
	
	
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
DebugCamera::~DebugCamera()
{
	Camera::~Camera();
}

/// <summary>
/// �X�V
/// </summary>
void DebugCamera::Update()
{
	// �}�E�X�����擾
	MouseUtil* mouse = MouseUtil::GetInstance();
	mouse->Update();

	//�}�E�X�̍��{�^���������ꂽ
	if (mouse->IsTriggered(MouseUtil::Button::Left))
	{
		DirectX::XMINT2 pos = mouse->GetPos();

		//�}�E�X�̍��W���擾
		m_drag.x = pos.x;
		m_drag.y = pos.y;
	}
	//�}�E�X�̍��{�^���������ꂽ��
	else if (mouse->IsReleased(MouseUtil::Button::Left))
	{
		m_nowAngle = m_afterAngle;
	}

	//�}�E�X�̃{�^����������Ă�����J�������ړ�������
	if (mouse->IsPressed(MouseUtil::Button::Left))
	{
		DirectX::XMINT2 pos = mouse->GetPos();
		Motion(pos.x, pos.y);
	}

	//�}�E�X�̃t�H�C�[���l���擾
	m_scrollWheelValue = mouse->GetWheelValue();

	if (m_scrollWheelValue > 0)
	{
		m_scrollWheelValue = 0;
		mouse->ResetWheelValue();
	}

	//�r���[�s����Z�o����
	Matrix rotX = Matrix::CreateRotationX(m_afterAngle.x);
	Matrix rotY = Matrix::CreateRotationY(m_afterAngle.y);

	Matrix rt = rotX * rotY;

	Vector3 eye(0.0f, 0.0f, 1.0f);
	Vector3 target(0.0f, 0.0f, 0.0f);
	Vector3 up(0.0f, 1.0f, 0.0f);

	eye = Vector3::Transform(eye, rt.Invert());
	eye *= (DEFAULT_CAMERA_DISTANCE - m_scrollWheelValue / 100);
	up = Vector3::Transform(up, rt.Invert());

	Camera::SetEyepos(eye);
	Camera::SetRefpos(target);
	Camera::SetUpvec(up);
	Camera::Update();
}



//�����֐�====================================================
/// <summary>
/// �ړ���̍s����v�Z
/// </summary>
/// <param name="x">�}�E�X�̍��W.x</param>
/// <param name="y">�}�E�X�̍��W.y</param>
void DebugCamera::Motion(int x, int y)
{
	//�}�E�X�|�C���^�̈ʒu�̃h���b�O�J�n�ʒu����ψ�(���Βl)
	float dx = (x - m_drag.x) * m_relativeScale.x;
	float dy = (y - m_drag.y) * m_relativeScale.y;

	if (dx != 0.0f || dy != 0.0f)
	{
		//X���̉�]
		float xAngle = dx * DirectX::XM_PI;
		//Y���̉�]
		float yAngle = dy * DirectX::XM_PI;

		//��]��̊p�x���i�[
		m_afterAngle.x = m_nowAngle.x + xAngle;
		m_afterAngle.y = m_nowAngle.y + yAngle;
	}
}