//
//デバック用カメラ
//
//Motoya Ito
//2017/10/16
//参考資料:学校配布のプロジェクト
#include "DebugCamera.h"

#include <Mouse.h>

#include "..//..//Mouse//MouseUtil.h"

//静的変数の実体
const float DebugCamera::DEFAULT_CAMERA_DISTANCE = 5.0f;

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="width">画面の横のサイズ</param>
/// <param name="height">画面の縦のサイズ</param>
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
/// デストラクタ
/// </summary>
DebugCamera::~DebugCamera()
{
	Camera::~Camera();
}

/// <summary>
/// 更新
/// </summary>
void DebugCamera::Update()
{
	// マウス情報を取得
	MouseUtil* mouse = MouseUtil::GetInstance();
	mouse->Update();

	//マウスの左ボタンが押された
	if (mouse->IsTriggered(MouseUtil::Button::Left))
	{
		DirectX::XMINT2 pos = mouse->GetPos();

		//マウスの座標を取得
		m_drag.x = pos.x;
		m_drag.y = pos.y;
	}
	//マウスの左ボタンが放されたら
	else if (mouse->IsReleased(MouseUtil::Button::Left))
	{
		m_nowAngle = m_afterAngle;
	}

	//マウスのボタンが押されていたらカメラを移動させる
	if (mouse->IsPressed(MouseUtil::Button::Left))
	{
		DirectX::XMINT2 pos = mouse->GetPos();
		Motion(pos.x, pos.y);
	}

	//マウスのフォイール値を取得
	m_scrollWheelValue = mouse->GetWheelValue();

	if (m_scrollWheelValue > 0)
	{
		m_scrollWheelValue = 0;
		mouse->ResetWheelValue();
	}

	//ビュー行列を算出する
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



//内部関数====================================================
/// <summary>
/// 移動先の行列を計算
/// </summary>
/// <param name="x">マウスの座標.x</param>
/// <param name="y">マウスの座標.y</param>
void DebugCamera::Motion(int x, int y)
{
	//マウスポインタの位置のドラッグ開始位置から変位(相対値)
	float dx = (x - m_drag.x) * m_relativeScale.x;
	float dy = (y - m_drag.y) * m_relativeScale.y;

	if (dx != 0.0f || dy != 0.0f)
	{
		//X軸の回転
		float xAngle = dx * DirectX::XM_PI;
		//Y軸の回転
		float yAngle = dy * DirectX::XM_PI;

		//回転後の角度を格納
		m_afterAngle.x = m_nowAngle.x + xAngle;
		m_afterAngle.y = m_nowAngle.y + yAngle;
	}
}