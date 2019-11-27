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
staticメンバ
***************************************/
const float PlayerActor::SpeedMove = 0.6f;
const D3DXVECTOR3 PlayerActor::BorderMove = { 45.0f, 25.0f, 0.0f };

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

	Move(direction);

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

/**************************************
移動処理
***************************************/
void PlayerActor::Move(const D3DXVECTOR3 & dir)
{
	D3DXVECTOR3 position = transform->GetPosition() + Vector3::Normalize(dir) * SpeedMove;

	position = Vector3::Clamp(-BorderMove, BorderMove, position);

	transform->SetPosition(position);
}
