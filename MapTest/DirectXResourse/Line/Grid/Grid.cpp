//
//ιΥΪπ`­NX
//ItoMotoya
//2017/10/16
//QlΏ:https://github.com/Microsoft/DirectXTK/wiki/Simple-rendering
#include "Grid.h"

#include <DirectXColors.h>

using namespace DirectX;
using namespace DirectX::SimpleMath;

//ΰΦ=====================================================================
void Grid::CreateGrid()
{

}

//publicΦ===================================================================
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
	//‘
	for (int i = 0; i < m_wonRowNam + 1; i++)
	{
		Vector3 lineStart = Vector3(-m_wonRowNam / 2, 0, i - (m_wonRowNam / 2));
		Vector3 lineEnd = Vector3(m_wonRowNam / 2, 0, i - (m_wonRowNam / 2));

		m_line->SetStartPos(lineStart);
		m_line->SetEndPos(lineEnd);

		m_line->Render();
	}

	//c
	for (int i = 0; i < m_wonRowNam + 1; i++)
	{
		Vector3 lineStart = Vector3(i - (m_wonRowNam / 2) , 0, -m_wonRowNam / 2);
		Vector3 lineEnd = Vector3(i - (m_wonRowNam / 2), 0, m_wonRowNam / 2);

		m_line->SetStartPos(lineStart);
		m_line->SetEndPos(lineEnd);

		m_line->Render();
	}
}
