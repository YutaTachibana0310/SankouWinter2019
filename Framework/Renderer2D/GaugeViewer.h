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

	void DrawFrame();
	void DrawGauge();
	
	//�����ݒ�i1.0f ~ 0.0f)
	void SetPercent(float percent);

private:
	float percent;

	void Draw() {}

	void SetGaugeVertex();
};

#endif