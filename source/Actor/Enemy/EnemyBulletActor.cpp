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
const int EnemyBulletActor::IntervalAnimation = 3;

/**************************************
コンストラクタ
***************************************/
EnemyBulletActor::EnemyBulletActor() :
	indexAnim(0)
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

	indexAnim = 0;
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
	cntFrame = Math::WrapAround(0, IntervalAnimation, ++cntFrame);
	if (cntFrame == 0)
	{
		++indexAnim;
	}

	transform->Move(transform->Forward() * 0.5f);
}

/**************************************
描画処理
***************************************/
void EnemyBulletActor::Draw()
{
	int indexTexture = EnemyBulletConfig::GetTextureIndex(type, indexAnim);
	polygon->SetTextureIndex(indexTexture);

	D3DXMATRIX mtxWorld = transform->GetMatrix();
	polygon->Draw(mtxWorld);
}

/**************************************
明かり処理
***************************************/
void EnemyBulletActor::DrawBloom()
{
	int indexTexture = EnemyBulletConfig::GetBloomTextureIndex(type, indexAnim);
	polygon->SetTextureIndex(indexTexture);

	D3DXMATRIX mtxWorld = transform->GetMatrix();
	polygon->Draw(mtxWorld);
}

/**************************************
タイプ設定
***************************************/
void EnemyBulletActor::SetType(EnemyBulletConfig::Type type)
{
	this->type = type;
}

/**************************************
衝突時の処理
***************************************/
void EnemyBulletActor::OnColliderHit(ColliderObserver * other)
{
}
