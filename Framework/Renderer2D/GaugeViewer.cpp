//=====================================
//
// GaugeViewer.cpp
// 機能:ゲージビューワ
// Author:GP12B332 21 立花雄太
//
//=====================================
#include "GaugeViewer.h"

/**************************************
グローバル変数
***************************************/

/**************************************
コンストラクタ
***************************************/
GaugeViewer::GaugeViewer() :
	percent(1.0f)
{
}

/**************************************
フレーム描画
***************************************/
void GaugeViewer::DrawFrame()
{
	SetUV(0.0f, 0.0f, 1.0f, 0.5f);

	Polygon2D::Draw();
}

/**************************************
ゲージ描画
***************************************/
void GaugeViewer::DrawGauge()
{
	SetGaugeVertex();

	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	pDevice->SetTexture(0, texture);

	pDevice->SetFVF(FVF_VERTEX_2D);

	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, vtxWk, sizeof(VERTEX_2D));
}

/**************************************
割合設定
***************************************/
void GaugeViewer::SetPercent(float percent)
{
	this->percent = percent;
}

/**************************************
ゲージ用の頂点設定
***************************************/
void GaugeViewer::SetGaugeVertex()
{
	float width = vtxSize.x * 2.0f;
	float height = vtxSize.y * 2.0f;

	D3DXVECTOR3 vtxGauge[NUM_VERTEX] = {};

	vtxGauge[0] = { -vtxSize.x, -vtxSize.y, 0.0f };
	vtxGauge[1] = vtxGauge[0] + D3DXVECTOR3(percent * width, 0.0f, 0.0f);
	vtxGauge[2] = { -vtxSize.x, vtxSize.y, 0.0f };
	vtxGauge[3] = vtxGauge[2] + D3DXVECTOR3(percent * width, 0.0f, 0.0f);

	D3DXMATRIX mtxTransform = transform->GetMatrix();
	for (int i = 0; i < NUM_VERTEX; i++)
	{
		D3DXVec3TransformCoord(&vtxWk[i].vtx, &vtxGauge[i], &mtxTransform);
	}

	SetUV(0.0f, 0.5f, percent, 0.5f);
}
