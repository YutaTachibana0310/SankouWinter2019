//=====================================
//
// EnemyBullet.cpp
// �@�\:
// Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "EnemyBulletActor.h"
#include "../../../Framework/Renderer3D/BoardPolygon.h"
#include "../../../Framework/Collider/BoxCollider3D.h"
#include "../../../Framework/Resource/ResourceManager.h"

/**************************************
�O���[�o���ϐ�
***************************************/
const D3DXVECTOR3 EnemyBulletActor::SizeCollider = { 1.0f, 1.0f, 1.0f };

/**************************************
�R���X�g���N�^
***************************************/
EnemyBulletActor::EnemyBulletActor()
{
	collider = BoxCollider3D::Create("EnemyBullet", transform);
	collider->SetSize(SizeCollider);
	collider->SetActive(false);
	collider->AddObserver(this);

	polygon = new BoardPolygon();
	ResourceManager::Instance()->GetPolygon("EnemyBullet", polygon);
	polygon->SetTexDiv({ 8.0f, 8.0f });
}

/**************************************
�f�X�g���N�^
***************************************/
EnemyBulletActor::~EnemyBulletActor()
{
	SAFE_DELETE(polygon);
	collider.reset();
}

/**************************************
����������
***************************************/
void EnemyBulletActor::Init(const Transform& shotTransform)
{
	*transform = shotTransform;

	collider->SetActive(true);
	active = true;
}

/**************************************
�I������
***************************************/
void EnemyBulletActor::Uninit()
{
	collider->SetActive(false);
	active = false;
}

/**************************************
�X�V����
***************************************/
void EnemyBulletActor::Update()
{
	transform->Move(transform->Forward() * 0.5f);
}

/**************************************
�`�揈��
***************************************/
void EnemyBulletActor::Draw()
{
	D3DXMATRIX mtxWorld = transform->GetMatrix();
	polygon->Draw(mtxWorld);
}

/**************************************
�Փˎ��̏���
***************************************/
void EnemyBulletActor::OnColliderHit(ColliderObserver * other)
{
}
