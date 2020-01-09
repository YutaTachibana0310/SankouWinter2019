//=====================================
//
// GaugeViewer.h
// 機能:
// Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _GAUGEVIEWER_H_
#define _GAUGEVIEWER_H_

#include "../../main.h"
#include "Polygon2D.h"

/**************************************
前方宣言
***************************************/

/**************************************
クラス定義
***************************************/
class GaugeViewer : public Polygon2D
{
public:
	GaugeViewer();

	void DrawFrame();
	void DrawGauge();
	
	//割合設定（1.0f ~ 0.0f)
	void SetPercent(float percent);

private:
	float percent;

	void Draw() {}

	void SetGaugeVertex();
};

#endif