//
//デバック用カメラ
//
//Motoya Ito
//2017/10/16
//参考資料:学校配布のプロジェクト
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
/// 更新
/// </summary>
void DebugCamera::Update()
{
	// マウス情報を取得
	
}
