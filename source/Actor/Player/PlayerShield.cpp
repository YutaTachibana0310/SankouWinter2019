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
#include "../../../Framework/Tween/Tween.h"

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
	collider->SetSize({ 5.0f, 3.0f, 6.0f });

	collider->SetActive(true);

	polygon = new BoardPolygon();
	ResourceManager::Instance()->GetPolygon("PlayerShield", polygon);
	polygon->SetDiffuse(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.9f));

	scaleY = std::make_shared<float>();
	onFinishBoundDown = std::bind(&PlayerShield::OnFinishBoundDown, this);

	OnFinishBoundDown();
}

/**************************************
�f�X�g���N�^
***************************************/
PlayerShield::~PlayerShield()
{
	collider.reset();
	SAFE_DELETE(polygon);
	scaleY.reset();
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

	transform->SetScale({ *scaleY, *scaleY, 1.0f });

	PDIRECT3DDEVICE9 pDevice = GetDevice();

	pDevice->SetRenderState(D3DRS_ZENABLE, false);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	auto mtxWorld = transform->GetMatrix();
	polygon->Draw(mtxWorld);

	pDevice->SetRenderState(D3DRS_ZENABLE, true);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	//collider->Draw();
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

/**************************************
�o�E���h�_�E���I������
***************************************/
void PlayerShield::OnFinishBoundDown()
{
	*scaleY = 1.1f;
	Tween::To(scaleY, 1.0f, 20.0f, EaseType::OutCubic, false, onFinishBoundDown);
}
