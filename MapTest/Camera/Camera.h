//
//カメラの基底クラス
//
//Motoya Ito
//2017/10/16
//参考資料:学校配布のプロジェクト
#pragma once

#include <d3d11_1.h>
#include <SimpleMath.h>

class Camera
{
protected:
	using Matrix = DirectX::SimpleMath::Matrix;
	using Vector3 = DirectX::SimpleMath::Vector3;

protected:
	Matrix m_proj;		//プロジェクション行列(射影行列)
	float m_fovY;		//縦の写す範囲(垂直方向視野角)
	float m_aspect;		//縦横の比率(アスペクト比)
	float m_nearclip;	//手前の表示限界距離(ニアクリップ)
	float m_farclip;	//奥の表示限界距離(ファークリップ)

	Matrix m_view;		//ビュー行列
	Vector3 m_eyepos;	//視点(カメラの位置)
	Vector3 m_refpos;	//参照点(見る場所)
	Vector3 m_upvec;	//上方向ベクトル(どちらが上か)

public:
	Camera(int Width, int Height);
	virtual ~Camera();

	virtual void Update();

};