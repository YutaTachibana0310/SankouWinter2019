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
#include "../../../Framework/Renderer3D/BillboardTransform.h"

/**************************************
グローバル変数
***************************************/
const D3DXVECTOR3 EnemyBulletActor::SizeCollider = { 1.0f, 1.0f, 1.0f };
const int EnemyBulletActor::IntervalAnimation = 3;
const D3DXVECTOR3 EnemyBulletActor::BorderLeftTop = { 0.0f, 40.0f, -60.0f };
const D3DXVECTOR3 EnemyBulletActor::BorderRightBottom = { 0.0f, -40.0f, 60.0f };

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

	renderTransform = new BillboardTransform();
}

/**************************************
デストラクタ
***************************************/
EnemyBulletActor::~EnemyBulletActor()
{
	SAFE_DELETE(polygon);
	SAFE_DELETE(renderTransform);
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

	transform->Move(transform->Forward() * speed);

	if (!CheckMoveBorder())
	{
		Uninit();
	}

	//描画用のSRT情報設定
	renderTransform->SetPosition(transform->GetPosition());

	renderTransform->SetScale(transform->GetScale());

	D3DXVECTOR3 eulerAngle = transform->GetEulerAngle();
	renderTransform->SetRotation({ eulerAngle.z, 0.0f, 0.0f });
}

/**************************************
描画処理
***************************************/
void EnemyBulletActor::Draw()
{
	int indexTexture = EnemyBulletConfig::GetTextureIndex(type, indexAnim);
	polygon->SetTextureIndex(indexTexture);

	D3DXMATRIX mtxWorld = renderTransform->GetMatrix();
	polygon->Draw(mtxWorld);

	collider->Draw();
}

/**************************************
明かり処理
***************************************/
void EnemyBulletActor::DrawBloom()
{
	int indexTexture = EnemyBulletConfig::GetBloomTextureIndex(type, indexAnim);
	polygon->SetTextureIndex(indexTexture);

	D3DXMATRIX mtxWorld = renderTransform->GetMatrix();
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
タイプ設定
***************************************/
void EnemyBulletActor::SetSpeed(float speed)
{
	this->speed = speed;
}

/**************************************
衝突時の処理
***************************************/
void EnemyBulletActor::OnColliderHit(ColliderObserver * other)
{
	Uninit();
}

/**************************************
移動の境界判定
***************************************/
bool EnemyBulletActor::CheckMoveBorder() const
{
	D3DXVECTOR3 position = transform->GetPosition();
	D3DXVECTOR2 size = EnemyBulletConfig::SizePolygon;

	if (position.z - size.x < BorderLeftTop.z)
		return false;

	if (position.z + size.x > BorderRightBottom.z)
		return false;

	if (position.y + size.y > BorderLeftTop.y)
		return false;

	if (position.y - size.y < BorderRightBottom.y)
		return false;

	return true;
}
