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
const int EnemyBulletActor::IntervalAnimation = 3;

/**************************************
�R���X�g���N�^
***************************************/
EnemyBulletActor::EnemyBulletActor() :
	indexAnim(0)
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

	indexAnim = 0;
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
	cntFrame = Math::WrapAround(0, IntervalAnimation, ++cntFrame);
	if (cntFrame == 0)
	{
		++indexAnim;
	}

	transform->Move(transform->Forward() * 0.5f);
}

/**************************************
�`�揈��
***************************************/
void EnemyBulletActor::Draw()
{
	int indexTexture = EnemyBulletConfig::GetTextureIndex(type, indexAnim);
	polygon->SetTextureIndex(indexTexture);

	D3DXMATRIX mtxWorld = transform->GetMatrix();
	polygon->Draw(mtxWorld);
}

/**************************************
�����菈��
***************************************/
void EnemyBulletActor::DrawBloom()
{
	int indexTexture = EnemyBulletConfig::GetBloomTextureIndex(type, indexAnim);
	polygon->SetTextureIndex(indexTexture);

	D3DXMATRIX mtxWorld = transform->GetMatrix();
	polygon->Draw(mtxWorld);
}

/**************************************
�^�C�v�ݒ�
***************************************/
void EnemyBulletActor::SetType(EnemyBulletConfig::Type type)
{
	this->type = type;
}

/**************************************
�Փˎ��̏���
***************************************/
void EnemyBulletActor::OnColliderHit(ColliderObserver * other)
{
}
