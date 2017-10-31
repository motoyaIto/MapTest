//
//碁盤目を描くクラス
//ItoMotoya
//2017/10/16
//参考資料:https://github.com/Microsoft/DirectXTK/wiki/Simple-rendering
#pragma once
#include "..//Line.h"

#include "..//..//..//Camera//Camera.h"

class Grid : public Line
{
private:
	Vector3 m_axis_x;//x軸
	Vector3 m_axis_y;//y軸

	Vector3 m_origin;//原点
	int m_wonRowNam;//マスの合計

	Line* m_line;

private://内部関数
	void CreateGrid();
	
public:
	Grid();
	~Grid();

	void Update() override;

	void Render() override;

public://getter

public://setter
	void SetProj(Matrix proj){ m_line->SetProj(proj); }
	void SetView(Matrix view){ m_line->SetView(view); }
};