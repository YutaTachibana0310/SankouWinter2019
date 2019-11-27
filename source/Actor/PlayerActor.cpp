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
#include "../../Framework/Input/input.h"
#include "../../Framework/Tool/DebugWindow.h"

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
	D3DXVECTOR3 direction = Vector3::Zero;
	direction.x = Input::GetPressHorizontail();
	direction.y = Input::GetPressVertical();

	transform->Move(direction);

	Debug::Begin("Player");

	Debug::Text(transform->GetPosition(), "PlayerPos");

	Debug::End();
}

/**************************************
描画処理
***************************************/
void PlayerActor::Draw()
{
	transform->SetWorld();
	mesh->Draw();
}
