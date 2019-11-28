//=====================================
//
//PlayerBulletActor.cpp
//�@�\:�v���C���[�o���b�g�A�N�^�[
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "PlayerBulletActor.h"
#include "../../../Framework/Renderer3D/BoardPolygon.h"
#include "../../../Framework/Resource/ResourceManager.h"

/**************************************
static�����o
***************************************/
const float PlayerBulletActor::SpeedMove = 2.0f;
const D3DXVECTOR3 PlayerBulletActor::MoveBorder = { 50.0f, 30.0f, 0.0f };

/**************************************
�R���X�g���N�^
***************************************/
PlayerBulletActor::PlayerBulletActor()
{
	polygon = new BoardPolygon();
	ResourceManager::Instance()->GetPolygon("BlazeBullet", polygon);
}

/**************************************
�f�X�g���N�^
***************************************/
PlayerBulletActor::~PlayerBulletActor()
{
	SAFE_DELETE(polygon);
}

/**************************************
����������
***************************************/
void PlayerBulletActor::Init(const D3DXVECTOR3& position)
{
	active = true;
	transform->SetPosition(position);
}

/**************************************
�I������
***************************************/
void PlayerBulletActor::Uninit()
{
}

/**************************************
�X�V����
***************************************/
void PlayerBulletActor::Update()
{
	transform->Move(Vector3::Right * SpeedMove);

	if (_IsOutBorder())
	{
		active = false;
	}
}

/**************************************
�`�揈��
***************************************/
void PlayerBulletActor::Draw()
{
	polygon->Draw(transform->GetMatrix());
}

/**************************************
�ړ��͈̓`�F�b�N����
***************************************/
bool PlayerBulletActor::_IsOutBorder()
{
	D3DXVECTOR3 position = transform->GetPosition();

	if (fabsf(position.x) > MoveBorder.x)
		return true;

	if (fabsf(position.y) > MoveBorder.y)
		return true;

	return false;
}
