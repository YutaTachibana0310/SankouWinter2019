//=====================================
//
//RotateChargeEnemy.cpp
//機能:
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "RotateChargeEnemy.h"
#include "../../../Framework/Renderer3D/MeshContainer.h"
#include "../../../Framework/Collider/BoxCollider3D.h"
#include "../../../Framework/Resource/ResourceManager.h"
#include "../../../Framework/Core/ObjectPool.h"
#include "../../../Framework/Particle/BaseEmitter.h"

#include "../../Controller/EnemyTimeController.h"
#include "../../Handler/EnemyEventHandler.h"
#include "../../Effect/GameParticleManager.h"

/**************************************
グローバル変数
***************************************/

/**************************************
コンストラクタ
***************************************/
RotateChargeEnemy::RotateChargeEnemy(EnemyEventHandler* handler) :
	BaseSmallEnemy(handler),
	enableHoming(true),
	trailEmitter(nullptr)
{ 
	colliders.reserve(1);
	colliders.push_back(BoxCollider3D::Create("Enemy", transform));
	colliders[0]->SetSize({ 5.0f, 2.0f, 2.0f });
	colliders[0]->AddObserver(this);

	ResourceManager::Instance()->GetMesh("RotateEnemy", mesh);
}

/**************************************
デストラクタ
***************************************/
RotateChargeEnemy::~RotateChargeEnemy()
{

}

/**************************************
初期化処理
***************************************/
void RotateChargeEnemy::Init()
{
	active = true;
	SetCollider(true);
	enableHoming = true;

	trailEmitter = GameParticleManager::Instance()->Generate(GameEffect::EnemyTrail, *transform);
	if (trailEmitter != nullptr)
	{
		AddChild(trailEmitter);
		trailEmitter->SetLocalPosition(Vector3::Forward * 2.0f);
	}

	hp = 2.0f;
}

/**************************************
終了処理
***************************************/
void RotateChargeEnemy::Uninit()
{
	if (trailEmitter != nullptr)
	{
		RemoveChild(trailEmitter);
		trailEmitter->SetActive(false);
	}

	SetCollider(false);
	active = false;
	ObjectPool::Instance()->Destroy<RotateChargeEnemy>(this);
}

/**************************************
更新処理
***************************************/
void RotateChargeEnemy::Update()
{
	D3DXVECTOR3 playerPos = handle->GetPlayerPosition();
	D3DXVECTOR3 diff = playerPos - transform->GetPosition();

	float distance = D3DXVec3LengthSq(&diff);
	const float DistanceDisableHoming = 5.0f * 5.0f;

	if (distance > DistanceDisableHoming && enableHoming)
	{
		transform->LookAt(transform->GetPosition() - diff);
	}
	else if(enableHoming)
	{
		enableHoming = false;
	}

	auto forward = transform->Forward();
	transform->Move(0.8f * -forward * EnemyTimeController::GetTimeScale());

	if (!enableHoming)
	{
		const auto CurrentPosition = transform->GetPosition();
		if (CurrentPosition.z < -60.0f || fabsf(CurrentPosition.y) > 40.0f)
		{
			Uninit();
		}
	}
}

/**************************************
描画処理
***************************************/
void RotateChargeEnemy::Draw()
{
	transform->SetWorld();
	mesh->Draw();

	colliders[0]->Draw();
}

/**************************************
爆発処理
***************************************/
void RotateChargeEnemy::Explode()
{
	handle->SetBullet(*transform, EnemyBulletConfig::BlueRotate, 0.55f);
	BaseSmallEnemy::Explode();
}
