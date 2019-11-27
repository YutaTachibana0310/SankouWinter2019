//=====================================
//
//�`��G�t�F�N�g����[RendererEffect.cpp]
//Author:GP12A332 21 ���ԗY��
//
//=====================================
#include "RendererEffect.h"

/**************************************
static�ϐ�
***************************************/
D3DXMATRIX RendererEffect::mtxView;
D3DXMATRIX RendererEffect::mtxProjection;
std::vector<D3DXVECTOR4> RendererEffect::lightDir;
std::vector<D3DCOLORVALUE> RendererEffect::lightDiffuse;
std::vector<D3DCOLORVALUE> RendererEffect::lightAmbient;
std::vector<D3DCOLORVALUE> RendererEffect::lightSpecular;

/*************************************
�r���[�s��ݒ菈��
***************************************/
void RendererEffect::SetView(const D3DXMATRIX & viewMatrix)
{
	mtxView = viewMatrix;
}

/*************************************
�v���W�F�N�V�����s��ݒ菈��
***************************************/
void RendererEffect::SetProjection(const D3DXMATRIX & projectionMatrix)
{
	mtxProjection = projectionMatrix;
}

/*************************************
���C�g���ݒ菈��
***************************************/
void RendererEffect::SetLight(unsigned index, const D3DLIGHT9 & light)
{
	if (lightDir.size() <= index)
	{
		lightDir.resize(index + 1);
		lightDiffuse.resize(index + 1);
		lightAmbient.resize(index + 1);
		lightSpecular.resize(index + 1);
	}

	lightDir[index] = D3DXVECTOR4(light.Direction, 0.0f);
	lightDiffuse[index] = light.Diffuse;
	lightAmbient[index] = light.Ambient;
	lightSpecular[index] = light.Specular;
}

/**************************************
�}�e���A�����ݒ菈��
***************************************/
void RendererEffect::SetMaterial(const D3DMATERIAL9 & material)
{
	effect->SetFloatArray(hMatDiffuse, (float*)&material.Diffuse, 4);
	effect->SetFloatArray(hMatAmbient, (float*)&material.Ambient, 4);
	effect->SetFloatArray(hMatSpecular, (float*)&material.Specular, 4);
}

/**************************************
�ύX���f����
***************************************/
void RendererEffect::Commit()
{
	effect->SetMatrix(hView, &mtxView);
	effect->SetMatrix(hProjection, &mtxProjection);

	effect->SetVectorArray(hLightDirection, &lightDir[0], lightDir.size());
	effect->SetVectorArray(hLightDiffuse, (D3DXVECTOR4*)&lightDiffuse[0], lightDiffuse.size());
	effect->SetVectorArray(hLightAmbient, (D3DXVECTOR4*)&lightAmbient[0], lightAmbient.size());
	effect->SetVectorArray(hLightSpecular, (D3DXVECTOR4*)&lightSpecular[0], lightSpecular.size());

	effect->CommitChanges();
}

/**************************************
�`��J�n�錾
***************************************/
void RendererEffect::Begin()
{
	Commit();
	effect->Begin(0, 0);
}

/**************************************
�p�X�J�n�錾
***************************************/
void RendererEffect::BeginPass(DWORD pass)
{
	effect->BeginPass(pass);
}

/**************************************
�p�X�I���錾
***************************************/
void RendererEffect::EndPass()
{
	effect->EndPass();
}

/**************************************
�`��I���錾
***************************************/
void RendererEffect::End()
{
	effect->End();
}
