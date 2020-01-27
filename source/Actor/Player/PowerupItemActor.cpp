//=====================================
//
//PowerupItemActor.cpp
//�@�\:�p���[�A�b�v�A�C�e���A�N�^�[
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "PowerupItemActor.h"
#include "../../../Framework/Resource/ResourceManager.h"
#include "../../../Framework/Renderer3D/BoardPolygon.h"
#include "../../../Framework/Core/FixedTime.h"
#include "../../../Framework/Collider/BoxCollider3D.h"
#include "../../../Framework/Core/ObjectPool.h"

/**************************************
�O���[�o���ϐ�
***************************************/
const D3DXVECTOR3 PowerupItemActor::MoveBorder = { 0.0f, 25.0f, 45.0f };

/**************************************
�R���X�g���N�^
***************************************/
PowerupItemActor::PowerupItemActor() :
	moveDir(Vector3::Zero),
	cntFrame(0.0f)
{
	polygon = new BoardPolygon();
	ResourceManager::Instance()->GetPolygon("PowerupItem", polygon);

	collider = BoxCollider3D::Create("Item", transform);
	collider->SetSize({ 5.0f, 3.0f, 3.0f });
	collider->AddObserver(this);
}

/**************************************
�f�X�g���N�^
***************************************/
PowerupItemActor::~PowerupItemActor()
{
	SAFE_DELETE(polygon);
	collider.reset();
}

/**************************************
����������
***************************************/
void PowerupItemActor::Init()
{
	cntFrame = 0.0f;
	moveDir = Vector3::Random();
	moveDir.z = -fabsf(moveDir.z);
	moveDir.x = 0.0f;

	collider->SetActive(true);
}

/**************************************
�I������
***************************************/
void PowerupItemActor::Uninit()
{
	active = false;
	collider->SetActive(false);
	ObjectPool::Instance()->Destroy<PowerupItemActor>(this);
}

/**************************************
�X�V����
***************************************/
void PowerupItemActor::Update()
{
	if (!active)
		return;

	cntFrame += FixedTime::GetTimeScale();

	const float DurationBound = 1200.0f;
	const float Speed = 0.4f;

	if (cntFrame < DurationBound)
	{

		D3DXVECTOR3 currentPosition = transform->GetPosition();
		D3DXVECTOR3 moveOffset = moveDir * FixedTime::GetTimeScale() * Speed;

		if (fabsf(currentPosition.y + moveOffset.y) > MoveBorder.y)
		{
			moveDir.y *= -1.0f;
		}
		if (fabsf(currentPosition.z + moveOffset.z) > MoveBorder.z)
		{
			moveDir.z *= -1.0f;
		}
	}

	transform->Move(moveDir * FixedTime::GetTimeScale() * Speed);

	D3DXVECTOR3 currentPosition = transform->GetPosition();
	if (fabsf(currentPosition.y) >= 1.5f * MoveBorder.y || fabsf(currentPosition.z) >= 1.5f * MoveBorder.z)
	{
		Uninit();
	}
}

/**************************************
�`�揈��
***************************************/
void PowerupItemActor::Draw()
{
	D3DXMATRIX mtxWorld = transform->GetMatrix();
	polygon->Draw(mtxWorld);
}

/**************************************
�Փˏ���
***************************************/
void PowerupItemActor::OnColliderHit(ColliderObserver * other)
{
	Uninit();
}
