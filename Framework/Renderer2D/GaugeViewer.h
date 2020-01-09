//=====================================
//
// GaugeViewer.h
// �@�\:
// Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _GAUGEVIEWER_H_
#define _GAUGEVIEWER_H_

#include "../../main.h"
#include "Polygon2D.h"

/**************************************
�O���錾
***************************************/

/**************************************
�N���X��`
***************************************/
class GaugeViewer : public Polygon2D
{
public:
	GaugeViewer();

	virtual void DrawFrame();
	virtual void DrawGauge();
	
	//�����ݒ�i1.0f ~ 0.0f)
	virtual void SetPercent(float percent);

protected:
	float percent;

	virtual void Draw() {}

	void SetGaugeVertex();
};

#endif