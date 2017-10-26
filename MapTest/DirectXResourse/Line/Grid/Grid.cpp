//
//碁盤目を描くクラス
//ItoMotoya
//2017/10/16
//参考資料:https://github.com/Microsoft/DirectXTK/wiki/Simple-rendering
#include "Grid.h"

#include <DirectXColors.h>

using namespace DirectX;
using namespace DirectX::SimpleMath;

Grid::Grid()
	: m_axis_x(1.0f, 0.0f, 0.0f), m_axis_y(0.0f, 0.0f, 1.0f)
	, m_origin(Vector3::Zero)
	, m_wonRowNam(20)
{
	m_line = new Line();
}

Grid::~Grid()
{
	delete m_line;
}

void Grid::Update()
{
	m_line->Update();
}

void Grid::Render()
{
	for (int i = 0; i <= m_wonRowNam; i++)
	{
		float fPercent = float(i) / float(m_wonRowNam);//全体からどの位置に線を引くか

		Vector3 scale = m_axis_x * fPercent + m_origin;

		m_line->SetStartPos(scale - m_axis_y);
		m_line->SetEndPos(scale + m_axis_y);

		m_line->Render();
	}

	for (int i = 0; i <= m_wonRowNam; i++)
	{
		float fPercent = float(i) / float(m_wonRowNam);//全体からどの位置に線を引くか

		Vector3 scale = m_axis_y * fPercent + m_origin;

		m_line->SetStartPos(scale - m_axis_x);
		m_line->SetEndPos(scale + m_axis_x);

		m_line->Render();
	}
}
