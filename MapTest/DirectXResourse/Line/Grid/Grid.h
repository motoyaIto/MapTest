//
//��Ֆڂ�`���N���X
//ItoMotoya
//2017/10/16
//�Q�l����:https://github.com/Microsoft/DirectXTK/wiki/Simple-rendering
#pragma once

#include "..//Line.h"

class Grid : public Line
{
public:
	Grid();
	~Grid();

	void Update();

	void Render();
};