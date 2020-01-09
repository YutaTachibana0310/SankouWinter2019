//=====================================
//
// GaugeViewer.cpp
// �@�\:�Q�[�W�r���[��
// Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "GaugeViewer.h"

/**************************************
�O���[�o���ϐ�
***************************************/

/**************************************
�R���X�g���N�^
***************************************/
GaugeViewer::GaugeViewer() :
	percent(1.0f)
{
}

/**************************************
�t���[���`��
***************************************/
void GaugeViewer::DrawFrame()
{
	SetUV(0.0f, 0.0f, 1.0f, 0.5f);

	Polygon2D::Draw();
}

/**************************************
�Q�[�W�`��
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
�����ݒ�
***************************************/
void GaugeViewer::SetPercent(float percent)
{
	this->percent = percent;
}

/**************************************
�Q�[�W�p�̒��_�ݒ�
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
