//=====================================
//
//TimeBreakText.h
//�@�\:TIME BREAK�e�L�X�g
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _TIMEBREAKTEXT_H_
#define _TIMEBREAKTEXT_H_

#include "../../../main.h"

/**************************************
�O���錾
***************************************/
class Polygon2D;

/**************************************
�N���X��`
***************************************/
class TimeBreakText
{
public:
	TimeBreakText();
	~TimeBreakText();

	void Draw();

	void Set();

	void OnFinishIn();
	void OnFinishOut();

	static const D3DXVECTOR3 InitPositionUpper;
	static const D3DXVECTOR3 InitPositionLower;

	static const D3DXVECTOR3 PositionUpper;
	static const D3DXVECTOR3 PositionLower;

	static const D3DXVECTOR3 LastPositionUpper;
	static const D3DXVECTOR3 LastPositionLower;

private:
	Polygon2D *upper;
	Polygon2D *lower;
};

#endif