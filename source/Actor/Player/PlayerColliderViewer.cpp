//=====================================
//
// PlayerColliderVIewer.cpp
// 機能:
// Author:GP12B332 21 立花雄太
//
//=====================================
#include "PlayerColliderViewer.h"
#include "../../../Framework/Renderer3D/BoardPolygon.h"
#include "../../../Framework/Resource/ResourceManager.h"

/**************************************
グローバル変数
***************************************/
const int PlayerColliderViewer::PeriodAnimation = 7;
const int PlayerColliderViewer::MaxAnimation = 6;

/**************************************
コンストラクタ
***************************************/
PlayerColliderViewer::PlayerColliderViewer()
{
	polygon = new BoardPolygon();
	ResourceManager::Instance()->GetPolygon("PlayerCollider", polygon);
}

/**************************************
デストラクタ
***************************************/
PlayerColliderViewer::~PlayerColliderViewer()
{
	SAFE_DELETE(polygon);
}

/**************************************
更新処理
***************************************/
void PlayerColliderViewer::Update()
{
	cntFrame = Math::WrapAround(0, PeriodAnimation, ++cntFrame);
	if (cntFrame == 0)
	{
		animIndex = Math::WrapAround(0, MaxAnimation, ++animIndex);
	}
}

/**************************************
描画処理
***************************************/
void PlayerColliderViewer::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	pDevice->SetRenderState(D3DRS_ZENABLE, false);

	polygon->SetTextureIndex(animIndex);
	polygon->Draw(transform->GetMatrix());

	pDevice->SetRenderState(D3DRS_ZENABLE, true);
}
