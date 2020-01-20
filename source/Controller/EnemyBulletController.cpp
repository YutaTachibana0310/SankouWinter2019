//=====================================
//
// EnemyBulletController.cpp
// 機能:
// Author:GP12B332 21 立花雄太
//
//=====================================
#include "EnemyBulletController.h"
#include "../../Framework/Resource/ResourceManager.h"
#include "../../Framework/Core/ObjectPool.h"
#include "../../Framework/Tool/DebugWindow.h"
#include "../../Framework/Camera/Camera.h"
#include "../../Framework/Particle/BaseParticleController.h"

#include "../../Library/nameof/nameof.hpp"

#include "../Actor/Enemy/EnemyBulletActor.h"
#include "EnemyTimeController.h"

#include <algorithm>

#include "../Handler/EnemyEventHandler.h"

/**************************************
グローバル変数
***************************************/
const unsigned EnemyBulletController::MaxBullet = 4096;

/**************************************
コンストラクタ
***************************************/
EnemyBulletController::EnemyBulletController() :
	cntBullet(0)
{
	bulletContainer.reserve(4096);

	renderer = new BulletRenderer(this);
}

/**************************************
デストラクタ
***************************************/
EnemyBulletController::~EnemyBulletController()
{
	Utility::DeleteContainer(bulletContainer);
	SAFE_DELETE(renderer);
}

/**************************************
更新処理
***************************************/
void EnemyBulletController::Update()
{
	/*
	テスト用処理
	*/
	{
		static float cntDebug = 0.0f;
		if (cntDebug >= 10.0f)
		{
			Transform shotTransform;
			shotTransform.SetPosition({ 0.0f, 0.0f, 20.0f });
			EnemyEventHandler handle;
			handle.GiveEnemyBulletController(this);

			shotTransform.Rotate(30.0f, Vector3::Right);
			handle.SetWayBullet(shotTransform, EnemyBulletConfig::BlueNeedle, 0.5f, 3, 15.0f);

			shotTransform.Rotate(-60.0f, Vector3::Right);
			handle.SetWayBullet(shotTransform, EnemyBulletConfig::RedNeedle, 0.5f, 3, -15.0f);

			cntDebug -= 10.0f;
		}
		cntDebug += EnemyTimeController::GetTimeScale();
	}

	//更新
	for (auto&& bullet : bulletContainer)
	{
		bullet->Update();
	}

	//非アクティブになったバレットをObjectPoolへ移動
	for(auto&& bullet : bulletContainer)
	{
		if (bullet->IsActive())
			continue;

		bullet->Uninit();
		ObjectPool::Instance()->Destroy<EnemyBulletActor>(bullet);
		cntBullet--;
	}

	//削除したバレットをコンテナから除外
	auto itr = std::remove_if(bulletContainer.begin(), bulletContainer.end(), [](auto ptr)
	{
		return !ptr->IsActive();
	});
	bulletContainer.erase(itr, bulletContainer.end());
}

/**************************************
描画処理
***************************************/
void EnemyBulletController::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	pDevice->SetRenderState(D3DRS_ZENABLE, false);

	//インスタンシングでの描画
	renderer->Draw();

#ifdef _DEBUG
	//当たり判定のデバッグ表示
	for (auto&& bullet : bulletContainer)
	{
		bullet->Draw();
	}
#endif

	pDevice->SetRenderState(D3DRS_ZENABLE, true);
}

/**************************************
バレットセット処理
***************************************/
void EnemyBulletController::SetBullet(const Transform & shotTransform, EnemyBulletConfig::Type type, float speed)
{
	if (cntBullet >= MaxBullet)
	{
		Debug::Log("EnemyBullet is Max");
		return;
	}

	EnemyBulletActor* bullet = ObjectPool::Instance()->Create<EnemyBulletActor>();
	bullet->Init(shotTransform);

	bullet->SetType(type);
	bullet->SetSpeed(speed);

	bulletContainer.push_back(bullet);

	cntBullet++;
}

/**************************************
BulletRendererコンストラクタ
***************************************/
EnemyBulletController::BulletRenderer::BulletRenderer(EnemyBulletController * entity) :
	declare(NULL), effect(NULL), indexBuff(NULL), transformBuffer(NULL), uvBuffer(NULL),
	hMtxView(NULL), hMtxProjection(NULL), hMtxInvView(NULL),
	entity(entity)
{
	MakeVtxBuffer();
	MakeDeclaration();
	MakeTransformBuffer();
	MakeUVBuffer();
	MakeIndexBuffer();
	LoadEffect();

	ResourceManager::Instance()->GetTexture("data/TEXTURE/Enemy/EnemyBullet.png", texture);
}

/**************************************
BulletRendererデストラクタ
***************************************/
EnemyBulletController::BulletRenderer::~BulletRenderer()
{
	SAFE_RELEASE(declare);
	SAFE_RELEASE(effect);
	SAFE_RELEASE(indexBuff);
	SAFE_RELEASE(transformBuffer);
	SAFE_RELEASE(uvBuffer);
	SAFE_RELEASE(vtxBuff);
	SAFE_RELEASE(texture);
}

/**************************************
BulletRenderer描画処理
***************************************/
void EnemyBulletController::BulletRenderer::Draw()
{
	SetTransformBuffer();
	SetUVBuffer();

	D3DXMATRIX view, proj, invView;
	view = Camera::MainCamera()->GetViewMtx();
	proj = Camera::MainCamera()->GetProjectionMtx();
	invView = Camera::MainCamera()->GetInverseViewMtx();

	effect->SetMatrix(hMtxView, &view);
	effect->SetMatrix(hMtxProjection, &proj);
	effect->SetMatrix(hMtxInvView, &invView);

	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	pDevice->SetStreamSource(0, vtxBuff, 0, sizeof(ParticleUnit));
	pDevice->SetStreamSource(1, transformBuffer, 0, sizeof(D3DXMATRIX));
	pDevice->SetStreamSource(2, uvBuffer, 0, sizeof(D3DXVECTOR2));
	pDevice->SetIndices(indexBuff);
	pDevice->SetVertexDeclaration(declare);

	pDevice->SetStreamSourceFreq(0, D3DSTREAMSOURCE_INDEXEDDATA | cntBullet);
	pDevice->SetStreamSourceFreq(1, D3DSTREAMSOURCE_INSTANCEDATA | 1);
	pDevice->SetStreamSourceFreq(2, D3DSTREAMSOURCE_INSTANCEDATA | 1);

	pDevice->SetTexture(0, texture);

	effect->Begin(0, 0);
	effect->BeginPass(0);

	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, NUM_VERTEX, 0, NUM_POLYGON);

	effect->EndPass();
	effect->End();

	pDevice->SetStreamSourceFreq(0, 1);
	pDevice->SetStreamSourceFreq(1, 1);
	pDevice->SetStreamSourceFreq(2, 1);
}

/**************************************
BulletRendererエフェクト読み込み
***************************************/
void EnemyBulletController::BulletRenderer::LoadEffect()
{
	if (effect != NULL)
		return;

	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXCreateEffectFromFile(pDevice, "data/EFFECT/particle3D.cfx", 0, 0, D3DXSHADER_SKIPVALIDATION, 0, &effect, 0);

	hMtxView = effect->GetParameterByName(NULL, "mtxView");
	hMtxProjection = effect->GetParameterByName(NULL, "mtxProj");
	hMtxInvView = effect->GetParameterByName(NULL, "mtxInvView");
}

/**************************************
BulletRenderer頂点バッファ作成
***************************************/
void EnemyBulletController::BulletRenderer::MakeVtxBuffer()
{
	if (vtxBuff != NULL)
		return;

	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	pDevice->CreateVertexBuffer(sizeof(ParticleUnit) * NUM_VERTEX, 0, 0, D3DPOOL_MANAGED, &vtxBuff, 0);

	ParticleUnit *p;
	vtxBuff->Lock(0, 0, (void**)&p, 0);

	//単位サイズ設定
	p[0].vtx = D3DXVECTOR3(-EnemyBulletConfig::SizePolygon.x, EnemyBulletConfig::SizePolygon.y, 0.0f);
	p[1].vtx = D3DXVECTOR3(EnemyBulletConfig::SizePolygon.x, EnemyBulletConfig::SizePolygon.y, 0.0f);
	p[2].vtx = D3DXVECTOR3(-EnemyBulletConfig::SizePolygon.x, -EnemyBulletConfig::SizePolygon.y, 0.0f);
	p[3].vtx = D3DXVECTOR3(EnemyBulletConfig::SizePolygon.x, -EnemyBulletConfig::SizePolygon.y, 0.0f);

	//単位UV設定
	float u = 1.0f / EnemyBulletConfig::SplitTexture.x;
	float v = 1.0f / EnemyBulletConfig::SplitTexture.y;
	p[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	p[1].tex = D3DXVECTOR2(u, 0.0f);
	p[2].tex = D3DXVECTOR2(0.0f, v);
	p[3].tex = D3DXVECTOR2(u, v);

	vtxBuff->Unlock();
}

/**************************************
BulletRenderer頂点宣言作成
***************************************/
void EnemyBulletController::BulletRenderer::MakeDeclaration()
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
BulletRendererSRTバTッファ作成
***************************************/
void EnemyBulletController::BulletRenderer::MakeTransformBuffer()
{
	if (transformBuffer != NULL)
		return;

	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	pDevice->CreateVertexBuffer(sizeof(D3DXMATRIX) * MaxBullet * 2, 0, 0, D3DPOOL_MANAGED, &transformBuffer, 0);
}

/**************************************
BulletRendererUVバッファ作成
***************************************/
void EnemyBulletController::BulletRenderer::MakeUVBuffer()
{
	if (uvBuffer != NULL)
		return;

	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	pDevice->CreateVertexBuffer(sizeof(D3DXVECTOR2) * MaxBullet * 2, 0, 0, D3DPOOL_MANAGED, &uvBuffer, 0);
}

/**************************************
BulletRendererインデックスバッファ作成
***************************************/
void EnemyBulletController::BulletRenderer::MakeIndexBuffer()
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

/**************************************
BulletRendererSRT情報セット
***************************************/
void EnemyBulletController::BulletRenderer::SetTransformBuffer()
{
	cntBullet = 0;

	D3DXMATRIX *ptr;
	transformBuffer->Lock(0, 0, (void**)&ptr, 0);

	/*
	ブルーム分も一度に描画するために2回ループする
	*/
	for (auto&& bullet : entity->bulletContainer)
	{
		*ptr = bullet->GetWorldMtx();
		ptr++;
		++cntBullet;
	}

	for (auto&& bullet : entity->bulletContainer)
	{
		*ptr = bullet->GetWorldMtx();
		ptr++;
		++cntBullet;
	}

	transformBuffer->Unlock();
}

/**************************************
BulletRendererテクスチャ情報セット
***************************************/
void EnemyBulletController::BulletRenderer::SetUVBuffer()
{
	if (cntBullet == 0)
		return;

	D3DXVECTOR2 *ptr;
	uvBuffer->Lock(0, 0, (void**)&ptr, 0);

	for (auto&& bullet : entity->bulletContainer)
	{
		*ptr = bullet->GetUV();
		ptr++;
	}

	for (auto&& bullet : entity->bulletContainer)
	{
		*ptr = bullet->GetBloomUV();
		ptr++;
	}

	uvBuffer->Unlock();
}
