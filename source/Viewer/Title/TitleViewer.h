//=====================================
//
//TitleViewer.h
//�@�\:�^�C�g���r���[��
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _TITLEVIEWER_H_
#define _TITLEVIEWER_H_

#include "../../../main.h"

/**************************************
�O���錾
***************************************/
class Polygon2D;
class TitleGear;

/**************************************
�N���X��`
***************************************/
class TitleViewer
{
public:
	TitleViewer();
	~TitleViewer();

	void Update();
	void Draw();

private:
	Polygon2D * titleLogo;

	TitleGear *centerGear;
	TitleGear *rightGear;
	TitleGear *leftGear;
};

#endif