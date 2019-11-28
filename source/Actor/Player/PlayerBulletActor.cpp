//=====================================
//
//PlayerBulletActor.cpp
//機能:プレイヤーバレットアクター
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "PlayerBulletActor.h"
#include "../../../Framework/Renderer3D/BoardPolygon.h"
#include "../../../Framework/Resource/ResourceManager.h"

/**************************************
staticメンバ
***************************************/
const float PlayerBulletActor::SpeedMove = 2.0f;

/**************************************
コンストラクタ
***************************************/
PlayerBulletActor::PlayerBulletActor()
{
	polygon = new BoardPolygon();
	ResourceManager::Instance()->GetPolygon("BlazeBullet", polygon);
}

/**************************************
デストラクタ
***************************************/
PlayerBulletActor::~PlayerBulletActor()
{
	SAFE_DELETE(polygon);
}

/**************************************
初期化処理
***************************************/
void PlayerBulletActor::Init(const D3DXVECTOR3& position)
{
	active = true;
	transform->SetPosition(position);
}

/**************************************
終了処理
***************************************/
void PlayerBulletActor::Uninit()
{
}

/**************************************
更新処理
***************************************/
void PlayerBulletActor::Update()
{
	transform->Move(Vector3::Right * SpeedMove);
}

/**************************************
描画処理
***************************************/
void PlayerBulletActor::Draw()
{
	polygon->Draw(transform->GetMatrix());
}
