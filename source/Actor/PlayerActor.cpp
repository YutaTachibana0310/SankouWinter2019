//=====================================
//
//PlayerActor.cpp
//機能:プレイヤーアクター
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "PlayerActor.h"
#include "../../Framework/Renderer3D/MeshContainer.h"
#include "../../Framework/Resource/ResourceManager.h"

/**************************************
コンストラクタ
***************************************/
PlayerActor::PlayerActor()
{
	mesh = new MeshContainer();

	ResourceManager::Instance()->GetMesh("Player", mesh);
}

/**************************************
デストラクタ
***************************************/
PlayerActor::~PlayerActor()
{
	SAFE_DELETE(mesh);
}

/**************************************
初期化処理
***************************************/
void PlayerActor::Init()
{
	transform->SetPosition(Vector3::Zero);
}

/**************************************
終了処理
***************************************/
void PlayerActor::Uninit()
{
}

/**************************************
更新処理
***************************************/
void PlayerActor::Update()
{
}

/**************************************
描画処理
***************************************/
void PlayerActor::Draw()
{
	transform->SetWorld();
	mesh->Draw();
}
