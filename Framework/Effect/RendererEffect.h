//=====================================
//
// RendererEffect.h
// �@�\:�`��G�t�F�N�g
// Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _RENDEREREFFECT_H_
#define _RENDEREREFFECT_H_

#include "../../main.h"

#include <vector>

/**************************************
�N���X��`
***************************************/
class RendererEffect
{
public:
	RendererEffect() {}
	virtual ~RendererEffect() {}

	//�r���[�A�v���W�F�N�V�����s��ݒ菈��
	static void SetView(const D3DXMATRIX& viewMatrix);
	static void SetProjection(const D3DXMATRIX& projectionMatrix);

	//���C�g���ݒ菈��
	static void SetLight(unsigned index, const D3DLIGHT9& light);
	
	//�}�e���A���ݒ菈��
	virtual void SetMaterial(const D3DMATERIAL9& material);
	
	//�ύX���f����
	virtual void Commit(); 

	//�`��J�n�錾�A�`��I���錾
	virtual void Begin();
	virtual void BeginPass(DWORD pass);
	virtual void EndPass();
	virtual void End();

protected:
	LPD3DXEFFECT effect;

	static D3DXMATRIX mtxView;
	static D3DXMATRIX mtxProjection;

	static std::vector<D3DXVECTOR4> lightDir;
	static std::vector<D3DCOLORVALUE> lightDiffuse;
	static std::vector<D3DCOLORVALUE> lightAmbient;
	static std::vector<D3DCOLORVALUE> lightSpecular;

	D3DXHANDLE hWorld;
	D3DXHANDLE hView;
	D3DXHANDLE hProjection;

	D3DXHANDLE hMatDiffuse;
	D3DXHANDLE hMatAmbient;
	D3DXHANDLE hMatSpecular;

	D3DXHANDLE hLightDiffuse;
	D3DXHANDLE hLightAmbient;
	D3DXHANDLE hLightSpecular;
	D3DXHANDLE hLightDirection;
};

#endif