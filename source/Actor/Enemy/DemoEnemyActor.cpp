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
#include "../../../Framework/Tween/Tween.h"
#include "../../../Framework/Collider/BoxCollider3D.h"

/**************************************
コンストラクタ
***************************************/
DemoEnemyActor::DemoEnemyActor()
{
	mesh = new MeshContainer();
	ResourceManager::Instance()->GetMesh("DemoEnemy", mesh);

	collider = BoxCollider3D::Create("Enemy", transform);
	collider->AddObserver(this);
	collider->SetSize({ 5.0f, 8.0f, 7.0f });
}

/**************************************
デストラクタ
***************************************/
DemoEnemyActor::~DemoEnemyActor()
{
	SAFE_DELETE(mesh);
	collider.reset();
}

/**************************************
初期化処理
***************************************/
void DemoEnemyActor::Init()
{
	D3DXVECTOR3 InitPos = { 0.0f, 0.0f, 50.0f };
	D3DXVECTOR3 GoalPos = { 0.0f, 0.0f, 25.0f };

	Tween::Move(*this, InitPos, GoalPos, 60, EaseType::OutCirc);

	collider->SetActive(true);
}

/**************************************
終了処理
***************************************/
void DemoEnemyActor::Uninit()
{
	collider->SetActive(false);

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

#ifdef _DEBUG
	collider->Draw();
#endif
}

/**************************************
当たり判定処理
***************************************/
void DemoEnemyActor::OnColliderHit(ColliderObserver * other)
{
}
