//=====================================
//
//パーティクルレンダラー処理[ParticleRenderer.cpp]
//Author:GP12A332 21 立花雄太
//
//=====================================
#include "ParticleRenderer.h"
#include "BaseParticle.h"

/**************************************
マクロ定義
***************************************/

/**************************************
コンストラクタ
***************************************/
ParticleRenderer::ParticleRenderer() :
	declare(NULL), effect(NULL), indexBuff(NULL), transformBuff(NULL), uvBuff(NULL),
	hMtxInvView(NULL), hMtxProjection(NULL), hMtxView(NULL),
	count(0), pMatrix(NULL), pUV(NULL)
{
	MakeDeclaration();
	MakeTransformBuffer();
	MakeUVBuffer();
	MakeIndexBuffer();
	LoadEffect();
}

/**************************************
デストラクタ
***************************************/
ParticleRenderer::~ParticleRenderer()
{
	SAFE_RELEASE(declare);
	SAFE_RELEASE(effect);
	SAFE_RELEASE(indexBuff);
	SAFE_RELEASE(transformBuff);
	SAFE_RELEASE(uvBuff);
}

/**************************************
描画開始処理
***************************************/
void ParticleRenderer::BeginDraw()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//ビュー行列、プロジェクション行列、ビュー逆行列を取得
	D3DXMATRIX view, proj, invView, screenProj;
	pDevice->GetTransform(D3DTS_VIEW, &view);
	pDevice->GetTransform(D3DTS_PROJECTION, &proj);
	D3DXMatrixInverse(&invView, NULL, &view);
	invView._41 = invView._42 = invView._43 = 0.0f;

	D3DXMatrixIdentity(&screenProj);
	screenProj._11 = 2.0f / SCREEN_WIDTH;
	screenProj._22 = -2.0f / SCREEN_HEIGHT;
	screenProj._41 = -1;
	screenProj._42 = 1;

	//シェーダに各行列を設定
	effect->SetMatrix(hMtxView, &view);
	effect->SetMatrix(hMtxProjection, &proj);
	effect->SetMatrix(hMtxInvView, &invView);
	effect->SetMatrix(hScreenProj, &screenProj);

	//各頂点バッファを設定
	pDevice->SetStreamSource(1, transformBuff, 0, sizeof(D3DXMATRIX));
	pDevice->SetStreamSource(2, uvBuff, 0, sizeof(ParticleUV));
	pDevice->SetIndices(indexBuff);
	pDevice->SetVertexDeclaration(declare);

	//ストリーム周波数設定
	pDevice->SetStreamSourceFreq(1, D3DSTREAMSOURCE_INSTANCEDATA | 1);
	pDevice->SetStreamSourceFreq(2, D3DSTREAMSOURCE_INSTANCEDATA | 1);

	//シェーダによる描画開始
	effect->Begin(0, 0);
}

/**************************************
描画終了処理
***************************************/
void ParticleRenderer::EndDraw()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//シェーダによる描画終了
	effect->End();

	//ストリーム周波数復元
	pDevice->SetStreamSourceFreq(0, 1);
	pDevice->SetStreamSourceFreq(1, 1);
	pDevice->SetStreamSourceFreq(2, 1);
}

/**************************************
Transform情報埋め込み処理
***************************************/
void ParticleRenderer::BeginPass(DWORD pass)
{
	effect->BeginPass(pass);

	count = 0;
	transformBuff->Lock(0, 0, (void**)&pMatrix, 0);
	uvBuff->Lock(0, 0, (void**)&pUV, 0);
}

/**************************************
Transform情報埋め込み処理
***************************************/
void ParticleRenderer::EndPass()
{
	effect->EndPass();
}

/**************************************
Particle情報埋め込み処理
***************************************/
void ParticleRenderer::PushParticleParameter(const D3DXMATRIX & mtxWorld, const ParticleUV & uv)
{
	*pMatrix = mtxWorld;
	pMatrix++;

	*pUV = uv;
	pUV++;

	count++;

	if (count >= PARTICLE_NUM_MAX)
	{
		Draw();

		count = 0;
		transformBuff->Lock(0, 0, (void**)&pMatrix, 0);
		uvBuff->Lock(0, 0, (void**)&pUV, 0);
	}
}

/**************************************
描画処理
***************************************/
void ParticleRenderer::Draw()
{
	transformBuff->Unlock();
	uvBuff->Unlock();

	if (count == 0)
		return;

	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	pDevice->SetStreamSourceFreq(0, D3DSTREAMSOURCE_INDEXEDDATA | count);

	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, NUM_VERTEX, 0, NUM_POLYGON);
}

/**************************************
エフェクト読み込み処理
***************************************/
void ParticleRenderer::LoadEffect()
{
	if (effect != NULL)
		return;

	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXCreateEffectFromFile(pDevice, "data/EFFECT/particle3D.cfx", 0, 0, D3DXSHADER_SKIPVALIDATION, 0, &effect, 0);

	hMtxView = effect->GetParameterByName(NULL, "mtxView");
	hMtxProjection = effect->GetParameterByName(NULL, "mtxProj");
	hMtxInvView = effect->GetParameterByName(NULL, "mtxInvView");
	hScreenProj = effect->GetParameterByName(NULL, "mtxScreenProj");
}

/**************************************
頂点宣言作成処理
***************************************/
void ParticleRenderer::MakeDeclaration()
{
	if (declare != NULL)
		return;

	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DVERTEXELEMENT9 elems[] =
	{
		{ 0, 0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0 },	//単位頂点（頂点座標）
		{ 0, 12, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0 },	//単位頂点（テクスチャ座標）
		{ 1, 0, D3DDECLTYPE_FLOAT4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 1 },	//ワールド変換行列1行目）
		{ 1, 16, D3DDECLTYPE_FLOAT4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 2 },	//ワールド変換情報2行目
		{ 1, 32, D3DDECLTYPE_FLOAT4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 3 },	//ワールド変換情報3行目
		{ 1, 48, D3DDECLTYPE_FLOAT4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 4 },	//ワールド変換情報4行目
		{ 2, 0, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 5 },	//個別のテクスチャ
		D3DDECL_END()
	};
	pDevice->CreateVertexDeclaration(elems, &declare);
}

/**************************************
トランスフォームバッファ作成処理
***************************************/
void ParticleRenderer::MakeTransformBuffer()
{
	if (transformBuff != NULL)
		return;

	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	pDevice->CreateVertexBuffer(sizeof(D3DXMATRIX) * PARTICLE_NUM_MAX, 0, 0, D3DPOOL_MANAGED, &transformBuff, 0);
}

/**************************************
UVバッファ作成処理
***************************************/
void ParticleRenderer::MakeUVBuffer()
{
	if (uvBuff != NULL)
		return;

	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	pDevice->CreateVertexBuffer(sizeof(ParticleUV) * PARTICLE_NUM_MAX, 0, 0, D3DPOOL_MANAGED, &uvBuff, 0);
}

/**************************************
インデックスバッファ作成処理
***************************************/
void ParticleRenderer::MakeIndexBuffer()
{
	if (indexBuff != NULL)
		return;

	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	WORD index[] = { 0, 1, 2, 2, 1, 3 };
	pDevice->CreateIndexBuffer(sizeof(index), 0, D3DFMT_INDEX16, D3DPOOL_MANAGED, &indexBuff, 0);

	void* p;
	indexBuff->Lock(0, 0, &p, 0);
	memcpy(p, index, sizeof(index));
	indexBuff->Unlock();
}