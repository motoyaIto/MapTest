//
//��Ֆڂ�`���N���X
//ItoMotoya
//2017/10/16
//�Q�l����:https://github.com/Microsoft/DirectXTK/wiki/Simple-rendering
#pragma once
#include "..//Line.h"

#include "..//..//..//Camera//Camera.h"

class Grid : public Line
{
private:
	Vector3 m_axis_x;//x��
	Vector3 m_axis_y;//y��

	Vector3 m_origin;//���_
	int m_wonRowNam;//�}�X�̍��v

	Line* m_line;

private://�����֐�
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