//=====================================
//
// FleetEnemy.cpp
// 機能:
// Author:GP12B332 21 立花雄太
//
//=====================================
#include "FleetEnemy.h"
#include "../../../Framework/Renderer3D/MeshContainer.h"
#include "../../../Framework/Collider/BoxCollider3D.h"
#include "../../../Framework/Resource/ResourceManager.h"

#include "../../System/EnemyTween.h"
#include "../../Effect/GameParticleManager.h"

/**************************************
グローバル変数
***************************************/

/**************************************
コンストラクタ
***************************************/
FleetEnemy::FleetEnemy()
{	
	ResourceManager::Instance()->GetMesh("FleetEnemy", mesh);

	colliders.reserve(0);
	colliders.push_back(BoxCollider3D::Create("Enemy", transform));
	colliders[0]->SetSize({ 5.0f, 10.0f, 10.0f });
	colliders[0]->AddObserver(this);
}

/**************************************gae
デストラクタ
***************************************/
FleetEnemy::~FleetEnemy()
{
}

/**************************************
初期化処理
***************************************/
void FleetEnemy::Init()
{
	active = true;
	SetCollider(true);

	D3DXVECTOR3 InitPos = { 0.0f, -10.0f, 50.0f };
	D3DXVECTOR3 GoalPos = { 0.0f, -10.0f, 25.0f };

	EnemyTween::Move(*this, InitPos, GoalPos, 60, EaseType::OutCirc);

	SetCollider(true);

	hp = 50.0f;
}

/**************************************
終了処理
***************************************/
void FleetEnemy::Uninit()
{
	SetCollider(false);

	//α用に最初期化する
	Init();
}

/**************************************
更新処理
***************************************/
void FleetEnemy::Update()
{
	if (hp <= 0)
	{

		Uninit();
	}
}

/**************************************
描画処理
***************************************/
void FleetEnemy::Draw()
{
	transform->SetWorld();
	mesh->Draw();

	colliders[0]->Draw();
}
