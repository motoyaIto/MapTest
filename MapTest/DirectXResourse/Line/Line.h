//
//線
//ItoMotoya
//2017/09/20
#pragma once

#include "..//DirectXResourse.h"


#include <SimpleMath.h>



class Line : public DirectXResourse
{
private:
	using Matrix = DirectX::SimpleMath::Matrix;
	using Vector3 = DirectX::SimpleMath::Vector3;

private:
	DirectX::CommonStates* m_states;//ステータス
	DirectX::BasicEffect* m_effect;//エフェクト
	std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionColor>> m_batch;//頂点、ポジション、色で高速描画
	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_inputLayout;//入力レアウト

private:
	Matrix m_cameraWorld;
	Matrix m_cameraView;
	Matrix m_cameraProj;

	Vector3 m_startPos;
	Vector3 m_endPos;

public:
	Line();
	~Line();

	void Initialize();
	void Update();
	void Render();

public://getter

public://setter
	void SetView(Matrix CameraView) { m_cameraView = CameraView; }
	void SetProj(Matrix CameraProj) { m_cameraProj = CameraProj; }
	void SetStartPos(Vector3 startPos) { m_startPos = startPos; }
	void SetEndPos(Vector3 endPos) { m_endPos = endPos; }
	
};