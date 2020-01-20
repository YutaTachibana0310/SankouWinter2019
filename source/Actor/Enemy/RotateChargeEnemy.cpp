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

#include "../../System/EnemyTween.h"
#include "../../Effect/GameParticleManager.h"
#include "../../Controller/EnemyTimeController.h"

/**************************************
グローバル変数
***************************************/

/**************************************
コンストラクタ
***************************************/
RotateChargeEnemy::RotateChargeEnemy(EnemyEventHandler* handler) :
	BaseSmallEnemy(handler)
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

	D3DXVECTOR3 InitPos = { 0.0f, 10.0f, 50.0f };
	D3DXVECTOR3 GoalPos = { 0.0f, 10.0f, 25.0f };

	EnemyTween::Move(*this, InitPos, GoalPos, 60, EaseType::OutCirc);

	SetCollider(true);
	active = true;

	hp = 5.0f;
}

/**************************************
終了処理
***************************************/
void RotateChargeEnemy::Uninit()
{
	SetCollider(false);
	active = false;
	ObjectPool::Instance()->Destroy<RotateChargeEnemy>(this);
}

/**************************************
更新処理
***************************************/
void RotateChargeEnemy::Update()
{
	transform->Rotate(5.0f * EnemyTimeController::GetTimeScale(), Vector3::Forward);
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
