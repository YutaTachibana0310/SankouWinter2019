//=====================================
//
//BackViewer.cpp
//機能:背景UIビューワ
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "BackViewer.h"
#include "../../../Framework/Renderer2D/Polygon2D.h"
#include "../../../Framework/Tween/Tween.h"
#include "TimeBreakText.h"

/**************************************
グローバル変数
***************************************/

/**************************************
コンストラクタ
***************************************/
BackViewer::BackViewer()
{
	timeBreak = new TimeBreakText();
	greenBG = std::make_shared<Polygon2D>();
	
	greenBG->SetSize({ SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f });
	greenBG->SetPosition({ SCREEN_CENTER_X, SCREEN_CENTER_Y, 0.0f });
	greenBG->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
	greenBG->LoadTexture("data/TEXTURE/Viewer/GreenBG.png");
}

/**************************************
デストラクタ
***************************************/
BackViewer::~BackViewer()
{
	SAFE_DELETE(timeBreak);
	greenBG.reset();
}

/**************************************
描画処理
***************************************/
void BackViewer::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, true);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, false);

	greenBG->Draw();

	timeBreak->Draw();

	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, false);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, true);
}

/**************************************
TimeBreak再生処理
***************************************/
void BackViewer::PlayTimeBreak()
{
	timeBreak->Set(TimeBreakText::TimeBreak);
}

/**************************************
PowerUp再生処理
***************************************/
void BackViewer::PlayPowerUp()
{
	timeBreak->Set(TimeBreakText::PowerUp);
}

/*************************************
緑背景セット
***************************************/
void BackViewer::SetGreenBG(bool state)
{
	if (state == greenBGstate)
		return;

	float alpha = state ? 1.0f : 0.0f;
	float current = greenBG->GetDiffuse().a;

	Tween::Fade(greenBG, current, alpha, 20.0f, EaseType::Linear, false);
	greenBGstate = state;
}
