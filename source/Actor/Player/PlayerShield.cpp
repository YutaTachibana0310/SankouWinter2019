//=====================================
//
//PlayerShield.cpp
//�@�\:�v���C���[�V�[���h
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "PlayerShield.h"
#include "../../../Framework/Collider/BoxCollider3D.h"
#include "../../../Framework/Renderer3D/BoardPolygon.h"
#include "../../../Framework/Resource/ResourceManager.h"

/**************************************
�O���[�o���ϐ�
***************************************/

/**************************************
�R���X�g���N�^
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
�f�X�g���N�^
***************************************/
PlayerShield::~PlayerShield()
{
	collider.reset();
	SAFE_DELETE(polygon);
}

/**************************************
�X�V����
***************************************/
void PlayerShield::Update()
{
}

/**************************************
�`�揈��
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
�A�N�e�B�u�ݒ�
***************************************/
void PlayerShield::SetActive(bool state)
{
	active = state;
	collider->SetActive(state);
}

/**************************************
�Փ˔���
***************************************/
void PlayerShield::OnColliderHit(ColliderObserver * other)
{

}
