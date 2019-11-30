//=====================================
//
//RenderingTarget.cpp
//機能:レンダリングターゲットクラス
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "RenderingTarget.h"
#include "../Effect/SpriteEffect.h"

/**************************************
コンストラクタ
***************************************/
RenderingTarget::RenderingTarget(DWORD width, DWORD height)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//レンダリングターゲット作成
	pDevice->CreateTexture(width, height, 1, D3DUSAGE_RENDERTARGET, D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT, &renderingTexture, 0);
	renderingTexture->GetSurfaceLevel(0, &renderingSurface);

	//頂点バッファ作成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * NUM_VERTEX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&vtxBuff,
		0);

	VERTEX_2D *pVtx;
	vtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].vtx = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].vtx = D3DXVECTOR3((float)width, 0.0f, 0.0f);
	pVtx[2].vtx = D3DXVECTOR3(0.0f, (float)height, 0.0f);
	pVtx[3].vtx = D3DXVECTOR3((float)width, (float)height, 0.0f);

	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	pVtx[0].rhw =
		pVtx[1].rhw =
		pVtx[2].rhw =
		pVtx[3].rhw = 1.0f;

	pVtx[0].diffuse =
		pVtx[1].diffuse =
		pVtx[2].diffuse =
		pVtx[3].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	vtxBuff->Unlock();

	//描画エフェクト作成
	effect = new SpriteEffect({ 1.0f, 1.0f });
}

/**************************************
デストラクタ
***************************************/
RenderingTarget::~RenderingTarget()
{
	SAFE_RELEASE(renderingSurface);
	SAFE_RELEASE(renderingTexture);
	SAFE_RELEASE(vtxBuff);

	SAFE_DELETE(effect);
}

/**************************************
レンダリングターゲットセット処理
***************************************/
void RenderingTarget::Set()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	pDevice->GetRenderTarget(0, &defaultSurface);
	pDevice->SetRenderTarget(0, renderingSurface);

	pDevice->Clear(0, 0, D3DCLEAR_TARGET, 0, 1.0f, 0);
}

/**************************************
レンダリングターゲット復元処理
***************************************/
void RenderingTarget::Restore()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	pDevice->SetRenderTarget(0, defaultSurface);
	SAFE_RELEASE(defaultSurface);
}

/**************************************
描画処理
***************************************/
void RenderingTarget::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	pDevice->SetFVF(FVF_VERTEX_2D);

	pDevice->SetStreamSource(0, vtxBuff, 0, sizeof(VERTEX_2D));

	pDevice->SetTexture(0, renderingTexture);

	effect->Begin();
	effect->BeginPass(1);

	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);

	effect->EndPass();
	effect->End();
}

/**************************************
テクスチャ取得処理
***************************************/
LPDIRECT3DTEXTURE9 RenderingTarget::GetTexture()
{
	return renderingTexture;
}

/**************************************
サーフェイス取得処理
***************************************/
LPDIRECT3DSURFACE9 RenderingTarget::GetSurface()
{
	return renderingSurface;
}
