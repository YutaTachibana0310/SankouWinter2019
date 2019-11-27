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
更新処理
***************************************/
void PlayerTurretActor::Update()
{
	transform->Rotate(-2.0f, Vector3::Right);
}

/**************************************
描画処理
***************************************/
void PlayerTurretActor::Draw(const Transform & parent)
{
	transform->SetWorld(&parent.GetMatrix());
	mesh->Draw();
}
