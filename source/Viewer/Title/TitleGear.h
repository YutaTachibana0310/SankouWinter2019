//=====================================
//
//TitleGear.h
//�@�\:�^�C�g������
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _TITLEGEAR_H_
#define _TITLEGEAR_H_

#include "../../../main.h"

/**************************************
�O���錾
***************************************/
class Polygon2D;

/**************************************
�N���X��`
***************************************/
class TitleGear : public GameObject
{
public:
	TitleGear();
	~TitleGear();

	void Update();
	void Draw();

private:
	Polygon2D * innerGear;
	Polygon2D * outerGear;
};
#endif