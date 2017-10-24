//
//マウスクラス
//
//Motoya Ito
//2017/10/17
//参考資料:学校配布のプロジェクト
#pragma once

#include <Windows.h>

#include <DirectXMath.h>
#include <Mouse.h>

class MouseUtil
{
private:
	using Mouse = DirectX::Mouse;
	using Mode = DirectX::Mouse::Mode;

public://構造体
		//ボタン
	enum Button
	{
		Left,
		Middle,
		Right,

		Num
	};

private://静的変数
	static std::unique_ptr<MouseUtil> m_instance;

public://静的関数
	static MouseUtil* GetInstance();

protected:
	std::unique_ptr<Mouse> m_mouse;//マウス
	Mouse::State m_state;//マウスステート

	Mouse::ButtonStateTracker m_buttonStateTracker;//ボタンステートトラッカー
	bool* m_buttonStates[Button::Num];//ボタン押下状態
	Mouse::ButtonStateTracker::ButtonState* m_buttonTrackerStates[Button::Num];//ボタントリガー状態

public:
	MouseUtil(Mode mode = Mode::MODE_ABSOLUTE);
	~MouseUtil();

	void Update();
	
	bool IsPressed(Button button);//指定のボタンが押されたか
	bool IsTriggered(Button button);//指定のボタンのトリガーチェック
	bool IsReleased(Button button);//指定のボタンのリリースチェック
	
	void ResetWheelValue();//ホイール値のリセット

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
