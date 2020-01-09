//=====================================
//
// EnergyViewer.cpp
// �@�\:
// Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "EnergyViewer.h"
#include "../../../Framework/Renderer2D/TextViewer.h"
#include "../../../Framework/Tool/DebugWindow.h"

/**************************************
�O���[�o���ϐ�
***************************************/
const float EnergyViewer::GaugeAlpha = 0.9f;

/**************************************
�R���X�g���N�^
***************************************/
EnergyViewer::EnergyViewer()
{
	LoadTexture("data/TEXTURE/Viewer/EnergyGauge.png");
	SetSize({ 250.0f, 25.0f});
	transform->SetPosition({ 900.0f, 75.0f, 0.0f });

	caption = new TextViewer("BadFennec", 40);
	caption->SetHorizontalAlignment(TextViewer::HorizontalAlignment::Right);
	caption->SetText("ENERGY");
	
	caption->UseOutLine(true);
	caption->SetOutlineColor(D3DXCOLOR(0.5f, 0.0f, 0.0f, 1.0f));
	caption->SetOutlineWidth(5);

	caption->SetPosition({ 1150.0f, 30.0f, 0.0f });

	SetPercent(1.0f);
}

/**************************************
�f�X�g���N�^
***************************************/
EnergyViewer::~EnergyViewer()
{
	SAFE_DELETE(caption);
}

/**************************************
�X�V����
***************************************/
void EnergyViewer::Update()
{

}

/**************************************
�`�揈��
***************************************/
void EnergyViewer::Draw()
{
	caption->Draw();

	if (percent < 0.2f)
	{
		SetColor({ 1.0f, 0.0f, 0.0f, GaugeAlpha });
	}
	else if (percent < 0.4f)
	{
		SetColor({ 1.0f, 1.0f, 0.0f, GaugeAlpha });
	}
	else
	{
		SetColor({ 0.0f, 1.0f, 1.0f, GaugeAlpha });
	}
	DrawGauge();

	SetColor({ 1.0f, 1.0f, 1.0f, 1.0f });
	DrawFrame();
}