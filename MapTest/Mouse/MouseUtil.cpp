//
//�}�E�X�N���X
//
//Motoya Ito
//2017/10/17
//�Q�l����:�w�Z�z�z�̃v���W�F�N�g
#include "MouseUtil.h"

#include <assert.h>

using namespace DirectX;

//�ÓI�ϐ��̎���
std::unique_ptr<MouseUtil> MouseUtil::m_instance;

/// <summary>
/// �ÓI�ϐ��̏�����
/// </summary>
/// <returns>���N���X�̃|�C���^�[</returns>
MouseUtil * MouseUtil::GetInstance()
{
	if (!m_instance)
	{
		m_instance = std::make_unique<MouseUtil>();
	}

	return m_instance.get();
}

/// <summary>
/// �R���X�g���N�^
/// </summary>
MouseUtil::MouseUtil(Mode mode)
{
	m_mouse = std::make_unique<Mouse>();
	m_mouse->SetMode(mode);

	// ������Ԃ̕ϐ��A�h���X���L�^
	m_buttonStates[Left] = &m_state.leftButton;
	m_buttonStates[Middle] = &m_state.middleButton;
	m_buttonStates[Right] = &m_state.rightButton;

	// �g���K�[��Ԃ̕ϐ��A�h���X���L�^
	m_buttonTrackerStates[Left] = &m_buttonStateTracker.leftButton;
	m_buttonTrackerStates[Middle] = &m_buttonStateTracker.middleButton;
	m_buttonTrackerStates[Right] = &m_buttonStateTracker.rightButton;
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
MouseUtil::~MouseUtil()
{
	
}

/// <summary>
/// �X�V
/// </summary>
void MouseUtil::Update()
{
	// �L�[�{�[�h�X�e�[�g���擾
	m_state = m_mouse->GetState();
	// �g���K�[��Ԃ̍X�V
	m_buttonStateTracker.Update(m_state);
}

/// <summary>
/// �w��̃{�^���������ꂽ��
/// </summary>
/// <param name="button">�w��̃{�^��</param>
/// <returns>�{�^����������Ă���(true)������Ă��Ȃ�(false)</returns>
bool MouseUtil::IsPressed(Button button)
{
	// �{�^���ԍ����͈͓���
	assert(0 <= button && button < Num);

	return *m_buttonStates[button];
}

/// <summary>
/// �w��̃{�^���̃g���K�[�`�F�b�N
/// </summary>
/// <param name="button">�w��̃{�^��</param>
/// <returns>�{�^���������ꂽ����(true)����ȊO(false)</returns>
bool MouseUtil::IsTriggered(Button button)
{
	// �{�^���ԍ����͈͓���
	assert(0 <= button && button < Num);

	// �����ꂽ���ォ
	if (*m_buttonTrackerStates[button] == Mouse::ButtonStateTracker::ButtonState::PRESSED)
	{
		return true;
	}

	return false;
}

/// <summary>
/// �w��̃{�^���̃����[�X�`�F�b�N
/// </summary>
/// <param name="button">�w��̃{�^��</param>
/// <returns>�{�^���������ꂽ��(true)���Ȃ�������(false)</returns>
bool MouseUtil::IsReleased(Button button)
{
	// �{�^���ԍ����͈͓��Ɏ��܂��Ă��邱�Ƃ��`�F�b�N
	assert(0 <= button && button < Num);

	// �g���K�[��
	if (*m_buttonTrackerStates[button] == Mouse::ButtonStateTracker::ButtonState::RELEASED)
	{
		return true;
	}

	return false;
}

/// <summary>
/// �z�C�[���l�̃��Z�b�g
/// </summary>
void MouseUtil::ResetWheelValue()
{
	m_mouse->ResetScrollWheelValue();
}

/// <summary>
/// ���[�h���擾
/// </summary>
/// <returns>���[�h</returns>
Mouse::Mode MouseUtil::GetMode()
{
	return m_state.positionMode;
}

/// <summary>
/// �}�E�X�̍��W���擾
/// </summary>
/// <returns>�}�E�X�̍��W</returns>
DirectX::XMINT2 MouseUtil::GetPos()
{
	XMINT2 pos;
	pos.x = m_state.x;
	pos.y = m_state.y;

	return pos;
}
