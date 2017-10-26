//
//碁盤目を描くクラス
//ItoMotoya
//2017/10/16
//参考資料:https://github.com/Microsoft/DirectXTK/wiki/Simple-rendering
#pragma once

#include "..//Line.h"

class Grid : public Line
{
private:
	Vector3 m_axis_x;//x軸
	Vector3 m_axis_y;//y軸

	Vector3 m_origin;//原点
	size_t m_wonRowNam;//マスの合計

	Line* m_line;

public:
	Grid();
	~Grid();

	void Update() override;

	void Render() override;
};