//=====================================
//
//RenderingTarget.h
//�@�\:�����_�����O�^�[�Q�b�g�N���X
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _RENDERINGTARGET_H_
#define _RENDERINGTARGET_H_

#include "../../main.h"

/**************************************
�O���錾
***************************************/
class SpriteEffect;

/**************************************
�N���X��`
***************************************/
class RenderingTarget
{
public:
	RenderingTarget(DWORD width, DWORD height);
	virtual ~RenderingTarget();

	virtual void Set();
	virtual void Restore();

	virtual void Draw();

	virtual LPDIRECT3DTEXTURE9 GetTexture();
	virtual LPDIRECT3DSURFACE9 GetSurface();

protected:
	LPDIRECT3DSURFACE9 defaultSurface;
	
	LPDIRECT3DTEXTURE9 renderingTexture;
	LPDIRECT3DSURFACE9 renderingSurface;

	LPDIRECT3DVERTEXBUFFER9 vtxBuff;

	SpriteEffect *effect;
};

#endif