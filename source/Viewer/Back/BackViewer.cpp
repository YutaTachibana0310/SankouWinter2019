//=====================================
//
//BackViewer.cpp
//機能:背景UIビューワ
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "BackViewer.h"
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
}

/**************************************
デストラクタ
***************************************/
BackViewer::~BackViewer()
{
	SAFE_DELETE(timeBreak);
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
	timeBreak->Set();
}
