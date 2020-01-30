//=====================================
//
//PlayerShield.cpp
//機能:プレイヤーシールド
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "PlayerShield.h"
#include "../../../Framework/Collider/BoxCollider3D.h"
#include "../../../Framework/Renderer3D/BoardPolygon.h"
#include "../../../Framework/Resource/ResourceManager.h"

/**************************************
グローバル変数
***************************************/

/**************************************
コンストラクタ
***************************************/
PlayerShield::PlayerShield()
{
	collider = BoxCollider3D::Create("PlayerShield", transform);
	collider->AddObserver(this);
	collider->SetSize({ 5.0f, 2.0f, 5.0f });

	collider->SetActive(true);

	polygon = new BoardPolygon();
	ResourceManager::Instance()->GetPolygon("PlayerShield", polygon);
	polygon->SetDiffuse(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.9f));
}

/**************************************
デストラクタ
***************************************/
PlayerShield::~PlayerShield()
{
	collider.reset();
	SAFE_DELETE(polygon);
}

/**************************************
更新処理
***************************************/
void PlayerShield::Update()
{
}

/**************************************
描画処理
***************************************/
void PlayerShield::Draw()
{
	D3DXVECTOR3 rotation = transform->GetEulerAngle();
	rotation.z = 0.0f;
	transform->SetRotation(rotation);

	PDIRECT3DDEVICE9 pDevice = GetDevice();

	pDevice->SetRenderState(D3DRS_ZENABLE, false);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	auto mtxWorld = transform->GetMatrix();
	polygon->Draw(mtxWorld);

	pDevice->SetRenderState(D3DRS_ZENABLE, true);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}

/**************************************
アクティブ設定
***************************************/
void PlayerShield::SetActive(bool state)
{
	active = state;
	collider->SetActive(state);
}

/**************************************
衝突判定
***************************************/
void PlayerShield::OnColliderHit(ColliderObserver * other)
{

}
