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
#include "../../Controller/EnemyTimeController.h"

/**************************************
�O���[�o���ϐ�
***************************************/
const D3DXVECTOR3 EnemyBulletActor::SizeCollider = { 0.25f, 0.25f, 0.25f };
const int EnemyBulletActor::IntervalAnimation = 3;
const D3DXVECTOR3 EnemyBulletActor::BorderLeftTop = { 0.0f, 40.0f, -60.0f };
const D3DXVECTOR3 EnemyBulletActor::BorderRightBottom = { 0.0f, -40.0f, 60.0f };

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

	renderTransform = new BillboardTransform();
}

/**************************************
�f�X�g���N�^
***************************************/
EnemyBulletActor::~EnemyBulletActor()
{
	SAFE_DELETE(polygon);
	SAFE_DELETE(renderTransform);
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
	Animation();

	Move();

	if (!CheckMoveBorder())
		active = false;

	//�`��p��SRT���ݒ�
	renderTransform->SetPosition(transform->GetPosition());
	renderTransform->SetScale(transform->GetScale());
	D3DXVECTOR3 eulerAngle = transform->GetEulerAngle();
	renderTransform->SetRotation({ eulerAngle.z, 0.0f, 0.0f });
}

/**************************************
�`�揈��
***************************************/
void EnemyBulletActor::Draw()
{
	collider->Draw();
}

/**************************************
�^�C�v�ݒ�
***************************************/
void EnemyBulletActor::SetType(EnemyBulletConfig::Type type)
{
	this->type = type;
}

/**************************************
�^�C�v�ݒ�
***************************************/
void EnemyBulletActor::SetSpeed(float speed)
{
	this->speed = speed;
}

/**************************************
���[���h�ϊ��s��擾����
***************************************/
D3DXMATRIX EnemyBulletActor::GetWorldMtx() const
{
	return renderTransform->GetMatrix();
}

/**************************************
UV���W�擾����
***************************************/
D3DXVECTOR2 EnemyBulletActor::GetUV() const
{
	return EnemyBulletConfig::GetTextureUV(type, indexAnim, false);
}

/**************************************
�u���[����UV���W�擾����
***************************************/
D3DXVECTOR2 EnemyBulletActor::GetBloomUV() const
{
	return EnemyBulletConfig::GetTextureUV(type, indexAnim, true);
}

/**************************************
�Փˎ��̏���
***************************************/
void EnemyBulletActor::OnColliderHit(ColliderObserver * other)
{
	//Uninit();
}

/**************************************
�A�j���[�V����
***************************************/
void EnemyBulletActor::Animation()
{
	cntFrame = Math::WrapAround(0, IntervalAnimation, ++cntFrame);
	if (cntFrame == 0)
	{
		++indexAnim;
	}
}

/**************************************
�ړ�
***************************************/
void EnemyBulletActor::Move()
{
	float deltaTime = type < EnemyBulletConfig::BlueRotate ? EnemyTimeController::GetTimeScale() : EnemyTimeController::GetBulletTimeScale();
	D3DXVECTOR3 offset = -transform->Forward() * speed * deltaTime;
	transform->Move(offset);
}

/**************************************
�ړ��̋��E����
***************************************/
bool EnemyBulletActor::CheckMoveBorder() const
{
	D3DXVECTOR3 position = transform->GetPosition();
	D3DXVECTOR2 size = EnemyBulletConfig::SizePolygon;

	if (position.z - size.x < BorderLeftTop.z)
		return false;

	if (position.z + size.x > BorderRightBottom.z)
		return false;

	if (position.y + size.y > BorderLeftTop.y)
		return false;

	if (position.y - size.y < BorderRightBottom.y)
		return false;

	return true;
}
