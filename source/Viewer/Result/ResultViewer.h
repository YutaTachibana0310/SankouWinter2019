//=====================================
//
//ResultViewer.h
//�@�\:���U���g�r���[��
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _RESULTVIEWER_H_
#define _RESULTVIEWER_H_

#include "../../../main.h"

/**************************************
�O���錾
***************************************/
class Polygon2D;

/**************************************
�N���X��`
***************************************/
class ResultViewer
{
public:
	ResultViewer();
	~ResultViewer();

	void Update();
	void Draw();

private:
	Polygon2D * bg;

};
#endif