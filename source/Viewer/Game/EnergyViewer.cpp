//=====================================
//
// EnergyViewer.cpp
// 機能:
// Author:GP12B332 21 立花雄太
//
//=====================================
#include "EnergyViewer.h"
#include "../../../Framework/Renderer2D/TextViewer.h"
#include "../../../Framework/Tool/DebugWindow.h"

/**************************************
グローバル変数
***************************************/
const float EnergyViewer::GaugeAlpha = 0.9f;

/**************************************
コンストラクタ
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
デストラクタ
***************************************/
EnergyViewer::~EnergyViewer()
{
	SAFE_DELETE(caption);
}

/**************************************
更新処理
***************************************/
void EnergyViewer::Update()
{

}

/**************************************
描画処理
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