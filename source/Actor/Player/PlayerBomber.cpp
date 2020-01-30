//=====================================
//
//PlayerBomber.cpp
//�@�\:�v���C���[�{���o�[
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "PlayerBomber.h"
#include "../../../Framework/Collider/BoxCollider3D.h"

/**************************************
�O���[�o���ϐ�
***************************************/

/**************************************
�R���X�g���N�^
***************************************/
PlayerBomberActor::PlayerBomberActor() :
	GameObject(false),
	cntFrame(0.0f)
{
	collider = BoxCollider3D::Create("PlayerBomber", transform);
	collider->SetSize({ 20.0f, 20.0f, 20.0f });
	collider->SetActive(false);
	collider->AddObserver(this);
}

/**************************************
�f�X�g���N�^
***************************************/
PlayerBomberActor::~PlayerBomberActor()
{
	collider.reset();
}

/**************************************
����������
***************************************/
void PlayerBomberActor::Init()
{
	cntFrame = 0.0f;
	collider->SetActive(true);
	active = true;
}

/**************************************
�I������
***************************************/
void PlayerBomberActor::Uninit()
{
	collider->SetActive(false);
	active = false;
}

/**************************************
�X�V����
***************************************/
void PlayerBomberActor::Update()
{
	if (!active)
		return;

	cntFrame += FixedTime::GetTimeScale();

	const float Duration = 270.0f;
	if (cntFrame >= Duration)
	{
		Uninit();
	}
}

void PlayerBomberActor::OnColliderHit(ColliderObserver * other)
{
}
