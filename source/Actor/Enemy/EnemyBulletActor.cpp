//=====================================
//
// EnemyBullet.cpp
// 機能:
// Author:GP12B332 21 立花雄太
//
//=====================================
#include "EnemyBulletActor.h"
#include "../../../Framework/Renderer3D/BoardPolygon.h"
#include "../../../Framework/Collider/BoxCollider3D.h"
#include "../../../Framework/Resource/ResourceManager.h"

/**************************************
グローバル変数
***************************************/
const D3DXVECTOR3 EnemyBulletActor::SizeCollider = { 1.0f, 1.0f, 1.0f };

/**************************************
コンストラクタ
***************************************/
EnemyBulletActor::EnemyBulletActor()
{
	collider = BoxCollider3D::Create("EnemyBullet", transform);
	collider->SetSize(SizeCollider);
	collider->SetActive(false);
	collider->AddObserver(this);

	polygon = new BoardPolygon();
	ResourceManager::Instance()->GetPolygon("EnemyBullet", polygon);
	polygon->SetTexDiv({ 8.0f, 8.0f });
}

/**************************************
デストラクタ
***************************************/
EnemyBulletActor::~EnemyBulletActor()
{
	SAFE_DELETE(polygon);
	collider.reset();
}

/**************************************
初期化処理
***************************************/
void EnemyBulletActor::Init(const Transform& shotTransform)
{
	*transform = shotTransform;

	collider->SetActive(true);
	active = true;
}

/**************************************
終了処理
***************************************/
void EnemyBulletActor::Uninit()
{
	collider->SetActive(false);
	active = false;
}

/**************************************
更新処理
***************************************/
void EnemyBulletActor::Update()
{
	transform->Move(transform->Forward() * 0.5f);
}

/**************************************
描画処理
***************************************/
void EnemyBulletActor::Draw()
{
	D3DXMATRIX mtxWorld = transform->GetMatrix();
	polygon->Draw(mtxWorld);
}

/**************************************
衝突時の処理
***************************************/
void EnemyBulletActor::OnColliderHit(ColliderObserver * other)
{
}
