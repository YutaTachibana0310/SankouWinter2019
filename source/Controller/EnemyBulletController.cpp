//=====================================
//
// EnemyBulletController.cpp
// �@�\:
// Author:GP12B332 21 ���ԗY��
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
�O���[�o���ϐ�
***************************************/
const unsigned EnemyBulletController::MaxBullet = 4096;

/**************************************
�R���X�g���N�^
***************************************/
EnemyBulletController::EnemyBulletController() :
	cntBullet(0)
{
	bulletContainer.reserve(4096);

	renderer = new BulletRenderer(this);
}

/**************************************
�f�X�g���N�^
***************************************/
EnemyBulletController::~EnemyBulletController()
{
	Utility::DeleteContainer(bulletContainer);
	SAFE_DELETE(renderer);
}

/**************************************
�X�V����
***************************************/
void EnemyBulletController::Update()
{
	/*
	�e�X�g�p����
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

	//�X�V
	for (auto&& bullet : bulletContainer)
	{
		bullet->Update();
	}

	//��A�N�e�B�u�ɂȂ����o���b�g��ObjectPool�ֈړ�
	for(auto&& bullet : bulletContainer)
	{
		if (bullet->IsActive())
			continue;

		bullet->Uninit();
		ObjectPool::Instance()->Destroy<EnemyBulletActor>(bullet);
		cntBullet--;
	}

	//�폜�����o���b�g���R���e�i���珜�O
	auto itr = std::remove_if(bulletContainer.begin(), bulletContainer.end(), [](auto ptr)
	{
		return !ptr->IsActive();
	});
	bulletContainer.erase(itr, bulletContainer.end());
}

/**************************************
�`�揈��
***************************************/
void EnemyBulletController::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	pDevice->SetRenderState(D3DRS_ZENABLE, false);

	//�C���X�^���V���O�ł̕`��
	renderer->Draw();

#ifdef _DEBUG
	//�����蔻��̃f�o�b�O�\��
	for (auto&& bullet : bulletContainer)
	{
		bullet->Draw();
	}
#endif

	pDevice->SetRenderState(D3DRS_ZENABLE, true);
}

/**************************************
�o���b�g�Z�b�g����
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
BulletRenderer�R���X�g���N�^
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
BulletRenderer�f�X�g���N�^
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
BulletRenderer�`�揈��
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
BulletRenderer�G�t�F�N�g�ǂݍ���
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
BulletRenderer���_�o�b�t�@�쐬
***************************************/
void EnemyBulletController::BulletRenderer::MakeVtxBuffer()
{
	if (vtxBuff != NULL)
		return;

	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	pDevice->CreateVertexBuffer(sizeof(ParticleUnit) * NUM_VERTEX, 0, 0, D3DPOOL_MANAGED, &vtxBuff, 0);

	ParticleUnit *p;
	vtxBuff->Lock(0, 0, (void**)&p, 0);

	//�P�ʃT�C�Y�ݒ�
	p[0].vtx = D3DXVECTOR3(-EnemyBulletConfig::SizePolygon.x, EnemyBulletConfig::SizePolygon.y, 0.0f);
	p[1].vtx = D3DXVECTOR3(EnemyBulletConfig::SizePolygon.x, EnemyBulletConfig::SizePolygon.y, 0.0f);
	p[2].vtx = D3DXVECTOR3(-EnemyBulletConfig::SizePolygon.x, -EnemyBulletConfig::SizePolygon.y, 0.0f);
	p[3].vtx = D3DXVECTOR3(EnemyBulletConfig::SizePolygon.x, -EnemyBulletConfig::SizePolygon.y, 0.0f);

	//�P��UV�ݒ�
	float u = 1.0f / EnemyBulletConfig::SplitTexture.x;
	float v = 1.0f / EnemyBulletConfig::SplitTexture.y;
	p[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	p[1].tex = D3DXVECTOR2(u, 0.0f);
	p[2].tex = D3DXVECTOR2(0.0f, v);
	p[3].tex = D3DXVECTOR2(u, v);

	vtxBuff->Unlock();
}

/**************************************
BulletRenderer���_�錾�쐬
***************************************/
void EnemyBulletController::BulletRenderer::MakeDeclaration()
{
	if (declare != NULL)
		return;

	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DVERTEXELEMENT9 elems[] =
	{
		{ 0, 0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0 },	//�P�ʒ��_�i���_���W�j
		{ 0, 12, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0 },	//�P�ʒ��_�i�e�N�X�`�����W�j
		{ 1, 0, D3DDECLTYPE_FLOAT4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 1 },	//���[���h�ϊ��s��1�s�ځj
		{ 1, 16, D3DDECLTYPE_FLOAT4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 2 },	//���[���h�ϊ����2�s��
		{ 1, 32, D3DDECLTYPE_FLOAT4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 3 },	//���[���h�ϊ����3�s��
		{ 1, 48, D3DDECLTYPE_FLOAT4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 4 },	//���[���h�ϊ����4�s��
		{ 2, 0, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 5 },	//�ʂ̃e�N�X�`��
		D3DDECL_END()
	};
	pDevice->CreateVertexDeclaration(elems, &declare);
}

/**************************************
BulletRendererSRT�oT�b�t�@�쐬
***************************************/
void EnemyBulletController::BulletRenderer::MakeTransformBuffer()
{
	if (transformBuffer != NULL)
		return;

	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	pDevice->CreateVertexBuffer(sizeof(D3DXMATRIX) * MaxBullet * 2, 0, 0, D3DPOOL_MANAGED, &transformBuffer, 0);
}

/**************************************
BulletRendererUV�o�b�t�@�쐬
***************************************/
void EnemyBulletController::BulletRenderer::MakeUVBuffer()
{
	if (uvBuffer != NULL)
		return;

	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	pDevice->CreateVertexBuffer(sizeof(D3DXVECTOR2) * MaxBullet * 2, 0, 0, D3DPOOL_MANAGED, &uvBuffer, 0);
}

/**************************************
BulletRenderer�C���f�b�N�X�o�b�t�@�쐬
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
BulletRendererSRT���Z�b�g
***************************************/
void EnemyBulletController::BulletRenderer::SetTransformBuffer()
{
	cntBullet = 0;

	D3DXMATRIX *ptr;
	transformBuffer->Lock(0, 0, (void**)&ptr, 0);

	/*
	�u���[��������x�ɕ`�悷�邽�߂�2�񃋁[�v����
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
BulletRenderer�e�N�X�`�����Z�b�g
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
