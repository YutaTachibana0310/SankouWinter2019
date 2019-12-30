//=====================================
//
// PlanetActor.cpp
// 機能:惑星アクター
// Author:GP12B332 21 立花雄太
//
//=====================================
#include "PlanetActor.h"
#include "../../Framework/Renderer3D/MeshContainer.h"
#include "../../Framework/Resource/ResourceManager.h"
#include "../../Framework/Tool/DebugWindow.h"

/**************************************
グローバル変数
***************************************/
const D3DXVECTOR3 PlanetActor::InitPos = { -500.0f, 200.0f, 200.0f };

/**************************************
コンストラクタ
***************************************/
PlanetActor::PlanetActor()
{
	mesh = new MeshContainer();
	ResourceManager::Instance()->GetMesh("Planet", mesh);

	transform->SetPosition(InitPos);
}

/**************************************
デストラクタ
***************************************/
PlanetActor::~PlanetActor()
{
	SAFE_DELETE(mesh);
}

/**************************************
更新処理
***************************************/
void PlanetActor::Update()
{

}

/**************************************
描画処理
***************************************/
void PlanetActor::Draw()
{
	transform->SetWorld();
	mesh->Draw();
}
