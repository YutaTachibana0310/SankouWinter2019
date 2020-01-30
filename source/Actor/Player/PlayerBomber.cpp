//=====================================
//
//PlayerBomber.cpp
//機能:プレイヤーボンバー
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "PlayerBomber.h"
#include "../../../Framework/Collider/BoxCollider3D.h"

/**************************************
グローバル変数
***************************************/

/**************************************
コンストラクタ
***************************************/
PlayerBomberActor::PlayerBomberActor() :
	GameObject(false),
	cntFrame(0.0f)
{
	collider = BoxCollider3D::Create("PlayerBomber", transform);
	collider->SetSize({ 20.0f, 20.0f, 20.0f });
	collider->SetActive(false);
	collider->AddObserver(this);
}

/**************************************
デストラクタ
***************************************/
PlayerBomberActor::~PlayerBomberActor()
{
	collider.reset();
}

/**************************************
初期化処理
***************************************/
void PlayerBomberActor::Init()
{
	cntFrame = 0.0f;
	collider->SetActive(true);
	active = true;
}

/**************************************
終了処理
***************************************/
void PlayerBomberActor::Uninit()
{
	collider->SetActive(false);
	active = false;
}

/**************************************
更新処理
***************************************/
void PlayerBomberActor::Update()
{
	if (!active)
		return;

	cntFrame += FixedTime::GetTimeScale();

	const float Duration = 270.0f;
	if (cntFrame >= Duration)
	{
		Uninit();
	}
}

void PlayerBomberActor::OnColliderHit(ColliderObserver * other)
{
}
