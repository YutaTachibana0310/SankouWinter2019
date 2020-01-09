//=====================================
//
// EnergyViewer.h
// �@�\:�G�l���M�[�r���[��
// Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _ENERGYVIEWER_H_
#define _ENERGYVIEWER_H_

#include "../../../main.h"
#include "../../../Framework/Renderer2D/GaugeViewer.h"

/**************************************
�O���錾
***************************************/
class GaugeViewer;
class TextViewer;

/**************************************
�N���X��`
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