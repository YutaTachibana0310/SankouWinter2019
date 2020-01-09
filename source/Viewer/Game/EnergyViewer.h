//=====================================
//
// EnergyViewer.h
// 機能:エネルギービューワ
// Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _ENERGYVIEWER_H_
#define _ENERGYVIEWER_H_

#include "../../../main.h"
#include "../../../Framework/Renderer2D/GaugeViewer.h"

/**************************************
前方宣言
***************************************/
class GaugeViewer;
class TextViewer;

/**************************************
クラス定義
***************************************/
class EnergyViewer : public GaugeViewer
{
public:
	EnergyViewer();
	~EnergyViewer();

	void Update();
	void Draw() override;

	static const float GaugeAlpha;

private:
	TextViewer *caption;
};

#endif