//=====================================
//
// FleetEnemy.cpp
// 機能:
// Author:GP12B332 21 立花雄太
//
//=====================================
#include "FleetEnemy.h"
#include "../../../Framework/Renderer3D/MeshContainer.h"
#include "../../../Framework/Collider/BoxCollider3D.h"
#include "../../../Framework/Resource/ResourceManager.h"

/**************************************
グローバル変数
***************************************/

/**************************************
コンストラクタ
***************************************/
FleetEnemy::FleetEnemy()
{
	
	ResourceManager::Instance()->GetMesh("FleetEnemy", mesh);
}

/**************************************
デストラクタ
***************************************/
FleetEnemy::~FleetEnemy()
{
}

/**************************************
初期化処理
***************************************/
void FleetEnemy::Init()
{
	active = true;
}

/**************************************
終了処理
***************************************/
void FleetEnemy::Uninit()
{
}

/**************************************
更新処理
***************************************/
void FleetEnemy::Update()
{

}

/**************************************
描画処理
***************************************/
void FleetEnemy::Draw()
{
	transform->SetWorld();
	mesh->Draw();
}
