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
#include "../../Controller/EnemyTimeController.h"

/**************************************
グローバル変数
***************************************/
const D3DXVECTOR3 EnemyBulletActor::SizeCollider = { 0.25f, 0.25f, 0.25f };
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
	Animation();

	Move();

	if (!CheckMoveBorder())
		active = false;

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
	collider->Draw();
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
ワールド変換行列取得処理
***************************************/
D3DXMATRIX EnemyBulletActor::GetWorldMtx() const
{
	return renderTransform->GetMatrix();
}

/**************************************
UV座標取得処理
***************************************/
D3DXVECTOR2 EnemyBulletActor::GetUV() const
{
	return EnemyBulletConfig::GetTextureUV(type, indexAnim, false);
}

/**************************************
ブルームのUV座標取得処理
***************************************/
D3DXVECTOR2 EnemyBulletActor::GetBloomUV() const
{
	return EnemyBulletConfig::GetTextureUV(type, indexAnim, true);
}

/**************************************
衝突時の処理
***************************************/
void EnemyBulletActor::OnColliderHit(ColliderObserver * other)
{
	//Uninit();
}

/**************************************
アニメーション
***************************************/
void EnemyBulletActor::Animation()
{
	cntFrame = Math::WrapAround(0, IntervalAnimation, ++cntFrame);
	if (cntFrame == 0)
	{
		++indexAnim;
	}
}

/**************************************
移動
***************************************/
void EnemyBulletActor::Move()
{
	float deltaTime = type < EnemyBulletConfig::BlueRotate ? EnemyTimeController::GetTimeScale() : EnemyTimeController::GetBulletTimeScale();
	D3DXVECTOR3 offset = -transform->Forward() * speed * deltaTime;
	transform->Move(offset);
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
