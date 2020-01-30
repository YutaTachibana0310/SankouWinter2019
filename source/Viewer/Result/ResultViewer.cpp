//=====================================
//
//ResultViewer.cpp
//機能:
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "ResultViewer.h"
#include "../../../Framework/Renderer2D/Polygon2D.h"

/**************************************
グローバル変数
***************************************/

/**************************************
コンストラクタ
***************************************/
ResultViewer::ResultViewer()
{
	bg = new Polygon2D();
	bg->LoadTexture("data/TEXTURE/Viewer/ResultBG.jpg");
	bg->SetSize({ SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f });
	bg->SetPosition({ SCREEN_CENTER_X, SCREEN_CENTER_Y, 0.0f });
}

/**************************************
デストラクタ
***************************************/
ResultViewer::~ResultViewer()
{
	SAFE_DELETE(bg);
}

/**************************************
更新処理
***************************************/
void ResultViewer::Update()
{
}

/**************************************
描画処理
***************************************/
void ResultViewer::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, true);

	bg->Draw();

	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, false);
}
