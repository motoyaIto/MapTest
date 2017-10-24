//
//�}�E�X�N���X
//
//Motoya Ito
//2017/10/17
//�Q�l����:�w�Z�z�z�̃v���W�F�N�g
#pragma once

#include <Windows.h>

#include <DirectXMath.h>
#include <Mouse.h>

class MouseUtil
{
private:
	using Mouse = DirectX::Mouse;
	using Mode = DirectX::Mouse::Mode;

public://�\����
		//�{�^��
	enum Button
	{
		Left,
		Middle,
		Right,

		Num
	};

private://�ÓI�ϐ�
	static std::unique_ptr<MouseUtil> m_instance;

public://�ÓI�֐�
	static MouseUtil* GetInstance();

protected:
	std::unique_ptr<Mouse> m_mouse;//�}�E�X
	Mouse::State m_state;//�}�E�X�X�e�[�g

	Mouse::ButtonStateTracker m_buttonStateTracker;//�{�^���X�e�[�g�g���b�J�[
	bool* m_buttonStates[Button::Num];//�{�^���������
	Mouse::ButtonStateTracker::ButtonState* m_buttonTrackerStates[Button::Num];//�{�^���g���K�[���

public:
	MouseUtil(Mode mode = Mode::MODE_ABSOLUTE);
	~MouseUtil();

	void Update();
	
	bool IsPressed(Button button);//�w��̃{�^���������ꂽ��
	bool IsTriggered(Button button);//�w��̃{�^���̃g���K�[�`�F�b�N
	bool IsReleased(Button button);//�w��̃{�^���̃����[�X�`�F�b�N
	
	void ResetWheelValue();//�z�C�[���l�̃��Z�b�g

public://getter
	Mode GetMode();
	DirectX::XMINT2 GetPos();

	int GetX() { return m_state.x; }
	int GetY() { return m_state.y; }

	int GetWheelValue() { return m_state.scrollWheelValue; }

public://setter
	void SetWindow(HWND windw) { m_mouse->SetWindow(windw); }
	void SetMode(Mode mode) { m_mouse->SetMode(mode); }

};
