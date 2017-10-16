//
//線
//ItoMotoya
//2017/09/20
#include "Line.h"

#include "..//..//pch.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

Line::Line()
{
}

Line::~Line()
{
}

void Line::Initialize()
{
	//デバイス依存の初期化=======================================================================
	m_states = new DirectX::CommonStates( m_d3dDevice.Get());

	m_effect = new DirectX::BasicEffect(m_d3dDevice.Get());
	m_effect->SetVertexColorEnabled(true);//頂点の色を有効にする

	//入力レイアウトの作成============================================================================
	void const* shaderByteCode;
	size_t byteCodeLength;

	//頂点シェーダの機械コードを取得
	m_effect->GetVertexShaderBytecode(&shaderByteCode, &byteCodeLength);

	//入力レイアウトに関連付ける
	DX::ThrowIfFailed(m_d3dDevice->CreateInputLayout(VertexPositionColor::InputElements
		, VertexPositionColor::InputElementCount
		, shaderByteCode, byteCodeLength
		, m_inputLayout.ReleaseAndGetAddressOf()));

	//頂点のポジションと色を初期化=========================================================
	m_batch = std::make_unique<PrimitiveBatch<VertexPositionColor>>(m_d3dContext.Get());


	//初期単位行列の取得
	m_cameraWorld = DirectX::SimpleMath::Matrix::Identity;
}

void Line::Update()
{
	m_cameraWorld = m_cameraView * m_cameraProj ;
}

void Line::Render()
{
	//第一引数でブレンド方法を確定(ノーマルブレンド)
	m_d3dContext->OMSetBlendState(m_states->Opaque(), nullptr, 0xFFFFFFFF);
	//深度ステンシル(深度バッファー、ステンシルバッファー)
	m_d3dContext->OMSetDepthStencilState(m_states->DepthNone(), 0);
	//サーフェイス上にレンダリング
	m_d3dContext->RSSetState(m_states->CullNone());

	//カメラのワールド行列をセットする
	m_effect->SetWorld(m_cameraWorld);
	//エフェクトを適用
	m_effect->Apply(m_d3dContext.Get());
	//入力レイアウトの適用
	m_d3dContext->IASetInputLayout(m_inputLayout.Get());

	m_batch->Begin();

	//ラインの長さ
	DirectX::SimpleMath::Vector3 xaxis(2.f, 0.f, 0.f);
	DirectX::SimpleMath::Vector3 yaxis(0.f, 0.f, 2.f);

	VertexPositionColor v1(m_startPos, Colors::White);//開始地点
	VertexPositionColor v2(m_endPos, Colors::White);//終了地点
	m_batch->DrawLine(v1, v2);//描画


	m_batch->End();
}
