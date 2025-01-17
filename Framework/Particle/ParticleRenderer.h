//=====================================
//
//パーティクルレンダラーヘッダ[ParticleRenderer.h]
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _PARTICLERENDERER_H_
#define _PARTICLERENDERER_H_

#include "../../main.h"
#include <vector>

/**************************************
マクロ定義
***************************************/
#define PARTICLE_NUM_MAX	(4096)

/**************************************
前方宣言
***************************************/
class BaseParticle;
class ParticleUV;

/**************************************
クラス定義
***************************************/
class ParticleRenderer
{
public:
	ParticleRenderer();
	~ParticleRenderer();

	void BeginDraw();
	void EndDraw();

	void BeginPass(DWORD pass);
	void EndPass();

	void PushParticleParameter(const D3DXMATRIX& mtxWorld, const ParticleUV& uv);

	void Draw();

private:
	LPDIRECT3DVERTEXDECLARATION9 declare;
	LPD3DXEFFECT effect;
	LPDIRECT3DINDEXBUFFER9 indexBuff;
	LPDIRECT3DVERTEXBUFFER9 transformBuff, uvBuff;
	D3DXHANDLE hMtxView, hMtxProjection, hMtxInvView, hScreenProj;

	UINT count;
	D3DXMATRIX *pMatrix;
	ParticleUV *pUV;

	void LoadEffect();
	void MakeDeclaration();
	void MakeTransformBuffer();
	void MakeUVBuffer();
	void MakeIndexBuffer();
};

#endif