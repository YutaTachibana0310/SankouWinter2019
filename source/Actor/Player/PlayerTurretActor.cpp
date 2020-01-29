//=====================================
//
//PlayerTurretActor.cpp
//機能:プレイヤー砲台アクター
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "PlayerTurretActor.h"
#include "../../../Framework/Resource/ResourceManager.h"
#include "../../../Framework/Renderer3D/MeshContainer.h"
#include "../../../Framework/Particle/BaseEmitter.h"
#include "../../Effect/GameParticleManager.h"

/**************************************
staticメンバ
***************************************/
const D3DXVECTOR3 PlayerTurretActor::OffsetShot = { 0.0f, 0.0f, 3.0f };

/**************************************
コンストラクタ
***************************************/
PlayerTurretActor::PlayerTurretActor() :
	trailEmitter(nullptr)
{
	mesh = new MeshContainer();
	ResourceManager::Instance()->GetMesh("PlayerTurret", mesh);

	trailEmitter = GameParticleManager::Instance()->Generate(GameEffect::PlayerTrail, transform->GetPosition());
	AddChild(trailEmitter);
	trailEmitter->SetLocalPosition(Vector3::Back * 1.0f);
	trailEmitter->SetLocalScale(Vector3::One * 0.5f);
}

/**************************************
デストラクタ
***************************************/
PlayerTurretActor::~PlayerTurretActor()
{
	SAFE_DELETE(mesh);
}

/**************************************
初期化処理
***************************************/
void PlayerTurretActor::Init()
{
	trailEmitter->SetActive(true);
}

/**************************************
終了処理
***************************************/
void PlayerTurretActor::Uninit()
{
	trailEmitter->SetActive(false);
}

/**************************************
更新処理
***************************************/
void PlayerTurretActor::Update()
{
	transform->Rotate(-2.0f * FixedTime::GetTimeScale(), Vector3::Forward);
}

/**************************************
描画処理
***************************************/
void PlayerTurretActor::Draw()
{
	transform->SetWorld();
	mesh->Draw();
}

/**************************************
発射位置取得処理
***************************************/
D3DXVECTOR3 PlayerTurretActor::GetShotPosition() const
{
	return transform->GetPosition() + OffsetShot;
}

/**************************************
PlayerTurretRoot更新処理
***************************************/
void PlayerTurretRoot::Update()
{
	const float AngleRotateTurret = 3.0f;
	transform->Rotate(AngleRotateTurret * FixedTime::GetTimeScale(), Vector3::Forward);
}
