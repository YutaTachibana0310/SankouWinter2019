//=====================================
//
// PlayerColliderVIewer.cpp
// �@�\:
// Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "PlayerColliderViewer.h"
#include "../../../Framework/Renderer3D/BoardPolygon.h"
#include "../../../Framework/Resource/ResourceManager.h"

/**************************************
�O���[�o���ϐ�
***************************************/
const int PlayerColliderViewer::PeriodAnimation = 7;
const int PlayerColliderViewer::MaxAnimation = 6;

/**************************************
�R���X�g���N�^
***************************************/
PlayerColliderViewer::PlayerColliderViewer()
{
	polygon = new BoardPolygon();
	ResourceManager::Instance()->GetPolygon("PlayerCollider", polygon);
}

/**************************************
�f�X�g���N�^
***************************************/
PlayerColliderViewer::~PlayerColliderViewer()
{
	SAFE_DELETE(polygon);
}

/**************************************
�X�V����
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
�`�揈��
***************************************/
void PlayerColliderViewer::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	pDevice->SetRenderState(D3DRS_ZENABLE, false);

	polygon->SetTextureIndex(animIndex);
	polygon->Draw(transform->GetMatrix());

	pDevice->SetRenderState(D3DRS_ZENABLE, true);
}
