//
//マウスクラス
//
//Motoya Ito
//2017/10/17
//参考資料:学校配布のプロジェクト
#include "MouseUtil.h"

#include <assert.h>

using namespace DirectX;

//静的変数の実体
std::unique_ptr<MouseUtil> MouseUtil::m_instance;

/// <summary>
/// 静的変数の初期化
/// </summary>
/// <returns>自クラスのポインター</returns>
MouseUtil * MouseUtil::GetInstance()
{
	if (!m_instance)
	{
		m_instance = std::make_unique<MouseUtil>();
	}

	return m_instance.get();
}

/// <summary>
/// コンストラクタ
/// </summary>
MouseUtil::MouseUtil(Mode mode)
{
	m_mouse = std::make_unique<Mouse>();
	m_mouse->SetMode(mode);

	// 押下状態の変数アドレスを記録
	m_buttonStates[Left] = &m_state.leftButton;
	m_buttonStates[Middle] = &m_state.middleButton;
	m_buttonStates[Right] = &m_state.rightButton;

	// トリガー状態の変数アドレスを記録
	m_buttonTrackerStates[Left] = &m_buttonStateTracker.leftButton;
	m_buttonTrackerStates[Middle] = &m_buttonStateTracker.middleButton;
	m_buttonTrackerStates[Right] = &m_buttonStateTracker.rightButton;
}

/// <summary>
/// デストラクタ
/// </summary>
MouseUtil::~MouseUtil()
{
	
}

/// <summary>
/// 更新
/// </summary>
void MouseUtil::Update()
{
	// キーボードステートを取得
	m_state = m_mouse->GetState();
	// トリガー状態の更新
	m_buttonStateTracker.Update(m_state);
}

/// <summary>
/// 指定のボタンが押されたか
/// </summary>
/// <param name="button">指定のボタン</param>
/// <returns>ボタンが押されている(true)押されていない(false)</returns>
bool MouseUtil::IsPressed(Button button)
{
	// ボタン番号が範囲内か
	assert(0 <= button && button < Num);

	return *m_buttonStates[button];
}

/// <summary>
/// 指定のボタンのトリガーチェック
/// </summary>
/// <param name="button">指定のボタン</param>
/// <returns>ボタンが押された直後(true)それ以外(false)</returns>
bool MouseUtil::IsTriggered(Button button)
{
	// ボタン番号が範囲内か
	assert(0 <= button && button < Num);

	// 押された直後か
	if (*m_buttonTrackerStates[button] == Mouse::ButtonStateTracker::ButtonState::PRESSED)
	{
		return true;
	}

	return false;
}

/// <summary>
/// 指定のボタンのリリースチェック
/// </summary>
/// <param name="button">指定のボタン</param>
/// <returns>ボタンが放されたら(true)いなかったら(false)</returns>
bool MouseUtil::IsReleased(Button button)
{
	// ボタン番号が範囲内に収まっていることをチェック
	assert(0 <= button && button < Num);

	// トリガーか
	if (*m_buttonTrackerStates[button] == Mouse::ButtonStateTracker::ButtonState::RELEASED)
	{
		return true;
	}

	return false;
}

/// <summary>
/// ホイール値のリセット
/// </summary>
void MouseUtil::ResetWheelValue()
{
	m_mouse->ResetScrollWheelValue();
}

/// <summary>
/// モードを取得
/// </summary>
/// <returns>モード</returns>
Mouse::Mode MouseUtil::GetMode()
{
	return m_state.positionMode;
}

/// <summary>
/// マウスの座標を取得
/// </summary>
/// <returns>マウスの座標</returns>
DirectX::XMINT2 MouseUtil::GetPos()
{
	XMINT2 pos;
	pos.x = m_state.x;
	pos.y = m_state.y;

	return pos;
}
