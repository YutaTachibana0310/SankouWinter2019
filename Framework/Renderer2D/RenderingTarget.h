//=====================================
//
//RenderingTarget.h
//機能:レンダリングターゲットクラス
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _RENDERINGTARGET_H_
#define _RENDERINGTARGET_H_

#include "../../main.h"

/**************************************
前方宣言
***************************************/
class SpriteEffect;

/**************************************
クラス定義
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