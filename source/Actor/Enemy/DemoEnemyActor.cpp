//=====================================
//
//DemoEnemyActor.cpp
//機能:
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "DemoEnemyActor.h"
#include "../../../Framework/Resource/ResourceManager.h"
#include "../../../Framework/Renderer3D/MeshContainer.h"
#include "../../../Framework/Collider/BoxCollider3D.h"

#include "../../Effect/GameParticleManager.h"
#include "../../System/EnemyTween.h"

/**************************************
コンストラクタ
***************************************/
DemoEnemyActor::DemoEnemyActor()
{
	mesh = new MeshContainer();
	ResourceManager::Instance()->GetMesh("DemoEnemy", mesh);

	colliders.resize(1, nullptr);
	colliders[0] = BoxCollider3D::Create("Enemy", transform);
	colliders[0]->AddObserver(this);
	colliders[0]->SetSize({ 5.0f, 8.0f, 7.0f });
}

/**************************************
デストラクタ
***************************************/
DemoEnemyActor::~DemoEnemyActor()
{
	SAFE_DELETE(mesh);
}

/**************************************
初期化処理
***************************************/
void DemoEnemyActor::Init()
{
	D3DXVECTOR3 InitPos = { 0.0f, 0.0f, 50.0f };
	D3DXVECTOR3 GoalPos = { 0.0f, 0.0f, 25.0f };

	EnemyTween::Move(*this, InitPos, GoalPos, 60, EaseType::OutCirc);

	SetCollider(true);

	hp = 50.0f;
}

/**************************************
終了処理
***************************************/
void DemoEnemyActor::Uninit()
{
	SetCollider(false);

	//α用に最初期化する
	Init();
}

/**************************************
更新処理
***************************************/
void DemoEnemyActor::Update()
{

}

/**************************************
描画処理
***************************************/
void DemoEnemyActor::Draw()
{
	transform->SetWorld();
	mesh->Draw();
}

/**************************************
当たり判定処理
***************************************/
void DemoEnemyActor::OnColliderHit(ColliderObserver * other)
{
	hp -= 1.0f;

	if (hp <= 0)
	{
		GameParticleManager::Instance()->GenerateEnemyExplostion(transform->GetPosition());
		Uninit();
	}
}
