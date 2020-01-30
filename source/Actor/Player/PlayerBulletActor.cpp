//=====================================
//
//PlayerBulletActor.cpp
//機能:プレイヤーバレットアクター
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "PlayerBulletActor.h"
#include "../../../Framework/Renderer3D/BoardPolygon.h"
#include "../../../Framework/Resource/ResourceManager.h"
#include "../../../Framework/Camera/Camera.h"
#include "../../../Framework/Collider/BoxCollider3D.h"

#include "../../Effect/GameParticleManager.h"
#include "../../System/GameScore.h"

/**************************************
staticメンバ
***************************************/
const float PlayerBulletActor::SpeedMove = 2.0f;
const D3DXVECTOR2 PlayerBulletActor::Size = { 2.0f, 1.0f };
const float PlayerBulletActor::PowerTable[] =
{
	0.5f,
	0.275f,
	0.2f,
	0.1625f
};

/**************************************
コンストラクタ
***************************************/
PlayerBulletActor::PlayerBulletActor() :
	power(1.0f)
{
	polygon = new BoardPolygon();
	transform->Rotate(-90.0f, Vector3::Up);

	collider = BoxCollider3D::Create("PlayerBullet", transform);
	collider->AddObserver(this);
	collider->SetSize({ 5.0f, 1.0f, 2.0f });
}

/**************************************
デストラクタ
***************************************/
PlayerBulletActor::~PlayerBulletActor()
{
	SAFE_DELETE(polygon);
	collider.reset();
}

/**************************************
初期化処理
***************************************/
void PlayerBulletActor::Init(const D3DXVECTOR3& position, bool isMain, int level)
{
	if (isMain)
	{
		ResourceManager::Instance()->GetPolygon("PlayerBulletMain", polygon);
		power = 1.0f;
	}
	else
	{
		ResourceManager::Instance()->GetPolygon("PlayerBullet", polygon);
		power = PowerTable[level];
	}

	active = true;
	transform->SetPosition(position);

	collider->SetActive(true);
}

/**************************************
終了処理
***************************************/
void PlayerBulletActor::Uninit()
{
	collider->SetActive(false);
}

/**************************************
更新処理
***************************************/
void PlayerBulletActor::Update()
{
	transform->Move(Vector3::Forward * SpeedMove * FixedTime::GetTimeScale());

	if (_IsOutBorder())
	{
		active = false;
	}
}

/**************************************
描画処理
***************************************/
void PlayerBulletActor::Draw()
{
	polygon->Draw(transform->GetMatrix());

#ifdef _DEBUG
	collider->Draw();
#endif
}

/**************************************
<演算子
***************************************/
bool PlayerBulletActor::operator<(const PlayerBulletActor & rhs) const
{
	return transform->GetPosition().z < rhs.GetPosition().z;
}

/**************************************
>演算子
***************************************/
bool PlayerBulletActor::operator>(const PlayerBulletActor & rhs) const
{
	return transform->GetPosition().z > rhs.GetPosition().z;
}

/**************************************
移動範囲チェック処理
***************************************/
bool PlayerBulletActor::_IsOutBorder()
{
	D3DXVECTOR3 position = transform->GetPosition();

	D3DXVECTOR3 leftTop = Camera::MainCamera()->Projection(position + D3DXVECTOR3(-Size.x, Size.y, 0.0f));
	if (leftTop.x < 0.0f || leftTop.y < -SCREEN_HEIGHT * 0.1f)
		return true;

	D3DXVECTOR3 rightBottom = Camera::MainCamera()->Projection(position + D3DXVECTOR3(Size.x, -Size.y, 0.0f));
	if(rightBottom.x > SCREEN_WIDTH * 1.05f || rightBottom.y > SCREEN_HEIGHT * 1.1f)
		return true;

	return false;
}

/**************************************
当たり判定処理
***************************************/
void PlayerBulletActor::OnColliderHit(ColliderObserver * other)
{
	active = false;
	GameParticleManager::Instance()->Generate(GameEffect::PlayerBulletHit, transform->GetPosition());
	GameScore::Instance()->AddScore(1);
}

