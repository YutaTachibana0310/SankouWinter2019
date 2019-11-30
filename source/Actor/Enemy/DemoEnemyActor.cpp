//=====================================
//
//DemoEnemyActor.cpp
//機能:
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "DemoEnemyActor.h"
#include "../../../Framework/Resource/ResourceManager.h"
#include "../../../Framework/Renderer3D/MeshContainer.h"
#include "../../../Framework/Tween/Tween.h"

/**************************************
コンストラクタ
***************************************/
DemoEnemyActor::DemoEnemyActor()
{
	mesh = new MeshContainer();
	ResourceManager::Instance()->GetMesh("DemoEnemy", mesh);
}

/**************************************
デストラクタ
***************************************/
DemoEnemyActor::~DemoEnemyActor()
{
	SAFE_DELETE(mesh);
}

/**************************************
初期化処理
***************************************/
void DemoEnemyActor::Init()
{
	D3DXVECTOR3 InitPos = { 50.0f, 0.0f, 0.0f };
	D3DXVECTOR3 GoalPos = { 25.0f, 0.0f, 0.0f };

	Tween::Move(*this, InitPos, GoalPos, 60, EaseType::OutCirc);
}

/**************************************
終了処理
***************************************/
void DemoEnemyActor::Uninit()
{
	//α用に最初期化する
	Init();
}

/**************************************
更新処理
***************************************/
void DemoEnemyActor::Update()
{
}

/**************************************
描画処理
***************************************/
void DemoEnemyActor::Draw()
{
	transform->SetWorld();
	mesh->Draw();
}
