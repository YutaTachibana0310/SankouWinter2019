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

/**************************************
staticメンバ
***************************************/
const D3DXVECTOR3 PlayerTurretActor::OffsetShot = { 0.0f, 0.0f, 3.0f };

/**************************************
コンストラクタ
***************************************/
PlayerTurretActor::PlayerTurretActor()
{
	mesh = new MeshContainer();
	ResourceManager::Instance()->GetMesh("PlayerTurret", mesh);
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
void PlayerTurretActor::Init(Transform * parent)
{
	this->parent = parent;
}

/**************************************
終了処理
***************************************/
void PlayerTurretActor::Uninit()
{
	parent = nullptr;
}

/**************************************
更新処理
***************************************/
void PlayerTurretActor::Update()
{
	transform->Rotate(-2.0f, Vector3::Forward);
}

/**************************************
描画処理
***************************************/
void PlayerTurretActor::Draw()
{
	transform->SetWorld(&parent->GetMatrix());
	mesh->Draw();
}

/**************************************
発射位置取得処理
***************************************/
D3DXVECTOR3 PlayerTurretActor::GetShotPosition() const
{
	D3DXMATRIX mtxWorld = transform->GetMatrix();
	mtxWorld *= parent->GetMatrix();

	D3DXVECTOR3 shotPos = { mtxWorld._41, mtxWorld._42, mtxWorld._43 };
	return shotPos + OffsetShot;
}
