//
//��Ֆڂ�`���N���X
//ItoMotoya
//2017/10/16
//�Q�l����:https://github.com/Microsoft/DirectXTK/wiki/Simple-rendering
#pragma once

#include "..//Line.h"

class Grid : public Line
{
private:
	Vector3 m_axis_x;//x��
	Vector3 m_axis_y;//y��

	Vector3 m_origin;//���_
	size_t m_wonRowNam;//�}�X�̍��v

	Line* m_line;

public:
	Grid();
	~Grid();

	void Update() override;

	void Render() override;
};