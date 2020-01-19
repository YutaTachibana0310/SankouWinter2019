//=====================================
//
//RotateChargeEnemy.cpp
//機能:
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "RotateChargeEnemy.h"
#include "../../../Framework/Renderer3D/MeshContainer.h"
#include "../../../Framework/Collider/BoxCollider3D.h"
#include "../../../Framework/Resource/ResourceManager.h"

/**************************************
グローバル変数
***************************************/

/**************************************
コンストラクタ
***************************************/
RotateChargeEnemy::RotateChargeEnemy()
{
	colliders.reserve(1);
	colliders.push_back(BoxCollider3D::Create("Enemy", transform));
	colliders[0]->SetSize({ 5.0f, 2.0f, 2.0f });

	ResourceManager::Instance()->GetMesh("RotateEnemy", mesh);
}

/**************************************
デストラクタ
***************************************/
RotateChargeEnemy::~RotateChargeEnemy()
{

}

/**************************************
初期化処理
***************************************/
void RotateChargeEnemy::Init()
{
	active = true;
	SetCollider(true);
}

/**************************************
終了処理
***************************************/
void RotateChargeEnemy::Uninit()
{
	SetCollider(false);
}

/**************************************
更新処理
***************************************/
void RotateChargeEnemy::Update()
{
	transform->Rotate(5.0f, Vector3::Forward);
}

/**************************************
描画処理
***************************************/
void RotateChargeEnemy::Draw()
{
	transform->SetWorld();
	mesh->Draw();

	colliders[0]->Draw();
}
