//=====================================
//
//TitleViewer.cpp
//機能:タイトルビューワ
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "TitleViewer.h"
#include "../../../Framework/Renderer2D/Polygon2D.h"

/**************************************
グローバル変数
***************************************/

/**************************************
コンストラクタ
***************************************/
TitleViewer::TitleViewer()
{
	titleLogo = new Polygon2D();
	titleLogo->LoadTexture("data/TEXTURE/Viewer/TitleLogo.png");
	titleLogo->SetSize({ 512.0f, 128.0f });
	titleLogo->SetPosition({ SCREEN_CENTER_X, 360.0f, 0.0f });
}

/**************************************
デストラクタ
***************************************/
TitleViewer::~TitleViewer()
{
	SAFE_DELETE(titleLogo);
}

/**************************************
更新処理
***************************************/
void TitleViewer::Update()
{

}

/**************************************
描画処理
***************************************/
void TitleViewer::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, true);

	titleLogo->Draw();

	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, false);
}
