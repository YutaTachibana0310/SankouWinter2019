//=====================================
//
//�|���S��2D����[Polygon2D.cpp]
//Author:GP12A332 21 ���ԗY��
//
//=====================================
#include "Polygon2D.h"
#include "../Resource/ResourceManager.h"

/**************************************
�}�N����`
***************************************/
#define POLYGON2D_DEFAULT_SIZE		(20.0f)

/**************************************
�R���X�g���N�^
***************************************/
Polygon2D::Polygon2D() :
	texture(NULL)
{
	SetSize({ POLYGON2D_DEFAULT_SIZE, POLYGON2D_DEFAULT_SIZE });
	SetUV(0.0f, 0.0f, 1.0f, 1.0f);

	vtxWk[0].diffuse =
		vtxWk[1].diffuse =
		vtxWk[2].diffuse =
		vtxWk[3].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	vtxWk[0].rhw =
		vtxWk[1].rhw =
		vtxWk[2].rhw =
		vtxWk[3].rhw = 1.0f;
}

/**************************************
�f�X�g���N�^
***************************************/
Polygon2D::~Polygon2D()
{
	SAFE_RELEASE(texture);
}

/**************************************
�`�揈��
***************************************/
void Polygon2D::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	pDevice->SetTexture(0, texture);

	pDevice->SetFVF(FVF_VERTEX_2D);

	SetVertex();

	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, vtxWk, sizeof(VERTEX_2D));
}

/**************************************
�T�C�Y�Z�b�g����
***************************************/
void Polygon2D::SetSize(const D3DXVECTOR2& size)
{
	vtxPos[0] = D3DXVECTOR3(-size.x * 1.0f, -size.y * 1.0f, 0.0f);
	vtxPos[1] = D3DXVECTOR3( size.x * 1.0f, -size.y * 1.0f, 0.0f);
	vtxPos[2] = D3DXVECTOR3(-size.x * 1.0f,  size.y * 1.0f, 0.0f);
	vtxPos[3] = D3DXVECTOR3( size.x * 1.0f,  size.y * 1.0f, 0.0f);

	vtxSize = size;
}

/**************************************
�J���[�Z�b�g����
***************************************/
void Polygon2D::SetColor(D3DXCOLOR color)
{
	vtxWk[0].diffuse =
		vtxWk[1].diffuse =
		vtxWk[2].diffuse =
		vtxWk[3].diffuse = color;
}

/**************************************
UV���W�ݒ菈��
***************************************/
void Polygon2D::SetUV(float left, float top, float width, float height)
{
	vtxUV[0] = D3DXVECTOR2(left, top);
	vtxUV[1] = D3DXVECTOR2(left + width, top);
	vtxUV[2] = D3DXVECTOR2(left, top + height);
	vtxUV[3] = D3DXVECTOR2(left + width, top + height);

	for (int i = 0; i < NUM_VERTEX; i++)
	{
		vtxWk[i].tex = vtxUV[i];
	}
}

/**************************************
�e�N�X�`���ǂݍ��ݏ���
***************************************/
void Polygon2D::LoadTexture(const char* path)
{
	SAFE_RELEASE(texture);

	ResourceManager::Instance()->GetTexture(path, texture);
}

/**************************************
���_���W�ݒ菈��
***************************************/
void Polygon2D::SetVertex()
{
	D3DXMATRIX mtxTransform = transform->GetMatrix();

	for (int i = 0; i < NUM_VERTEX; i++)
	{
		D3DXVec3TransformCoord(&vtxWk[i].vtx, &vtxPos[i], &mtxTransform);
	}
}