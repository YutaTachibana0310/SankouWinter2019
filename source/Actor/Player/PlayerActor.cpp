//=====================================
//
//PlayerActor.cpp
//�@�\:�v���C���[�A�N�^�[
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "PlayerActor.h"
#include "../../../Framework/Renderer3D/MeshContainer.h"
#include "../../../Framework/Resource/ResourceManager.h"
#include "../../../Framework/Input/input.h"
#include "../../../Framework/Tool/DebugWindow.h"
#include "../../../Framework/Core/ObjectPool.h"
#include "../../../Framework/Collider/BoxCollider3D.h"
#include "../../../Framework/Tween/Tween.h"
#include "../../../Framework/Core/ObjectPool.h"
#include "../../../Framework/Particle/BaseEmitter.h"
#include "../../../Framework/Task/TaskManager.h"

#include "../../Effect/GameParticleManager.h"

#include "PlayerTurretActor.h"
#include "PlayerBulletActor.h"
#include "PlayerColliderViewer.h"
#include "PlayerShield.h"

#include "../../System/GameInput.h"

/**************************************
static�����o
***************************************/
const float PlayerActor::SpeedMove = 0.6f;
const D3DXVECTOR3 PlayerActor::BorderMove = { 0.0f, 25.0f, 45.0f };
const D3DXVECTOR3 PlayerActor::ShotPosition = { 0.0f, 0.0f, 5.0f };
const float PlayerActor::MaxAngle = 40.0f;
const D3DXVECTOR3 PlayerActor::InitPos = { 0.0f, 0.0f, -55.0f };

/**************************************
�R���X�g���N�^
***************************************/
PlayerActor::PlayerActor() :
	GameObject(false),
	cntShotFrame(0),
	enableShot(false),
	enableMove(false),
	currentLevel(0),
	isInvincible(true)
{
	mesh = new MeshContainer();
	ResourceManager::Instance()->GetMesh("Player", mesh);

	turretRoot = new PlayerTurretRoot();
	AddChild(turretRoot);
	turretRoot->SetLocalPosition(Vector3::Zero);

	collider = BoxCollider3D::Create("Player", transform);
	collider->SetSize({ 0.5f, 0.5f, 0.5f });
	collider->AddObserver(this);

	colliderViewer = new PlayerColliderViewer();
	AddChild(colliderViewer);

	const unsigned MaxTurret = 8;
	turretContainer.reserve(MaxTurret);

	trailEmitter = GameParticleManager::Instance()->Generate(GameEffect::PlayerTrail, transform->GetPosition());
	AddChild(trailEmitter);
	trailEmitter->SetLocalPosition(Vector3::Back * 2.0f);

	shield = new PlayerShield();
	AddChild(shield);
	shield->SetActive(false);

	transform->SetPosition(InitPos);
}

/**************************************
�f�X�g���N�^
***************************************/
PlayerActor::~PlayerActor()
{
	SAFE_DELETE(mesh);
	SAFE_DELETE(turretRoot);
	SAFE_DELETE(colliderViewer);
	SAFE_DELETE(shield);
	collider.reset();
	Utility::DeleteContainer(turretContainer);
}

/**************************************
����������
***************************************/
void PlayerActor::Init()
{
	active = true;
	
	transform->SetRotation(Quaternion::Identity);

	const D3DXVECTOR3 StartPos = { 0.0f, 0.0f, -20.0f };
	auto callback = std::bind(&PlayerActor::OnFinishInitMove, this);
	transform->SetPosition(InitPos);
	Tween::Move(*this, InitPos, StartPos, 60.0f, EaseType::OutBack, false, callback);

	currentLevel = -1;
	PowerUp();

	trailEmitter->SetActive(true);

	shield->SetActive(true);
}

/**************************************
�I������
***************************************/
void PlayerActor::Uninit()
{
	collider->SetActive(false);
	active = false;

	for (auto&& turret : turretContainer)
	{
		turret->Uninit();
	}

	trailEmitter->SetActive(false);

	Tween::Move(*this, InitPos, 30.0f, EaseType::Linear, false);
}

/**************************************
�X�V����
***************************************/
void PlayerActor::Update()
{
	if (!active)
		return;

	D3DXVECTOR3 direction = Vector3::Zero;
	direction.z = Input::GetPressHorizontail();
	direction.y = Input::GetPressVertical();

	_Move(direction);

	_Rotate(direction.y);

	_Shot();

	_SlowDownEnemyBullet();

	_FireBomber();

	turretRoot->Update();
	for (auto&& turret : turretContainer)
	{
		turret->Update();
	}

	colliderViewer->Update();
}

/**************************************
�`�揈��
***************************************/
void PlayerActor::Draw()
{
	if (!active)
		return;

	transform->SetWorld();
	mesh->Draw();

	for (auto&& turret : turretContainer)
	{
		turret->Draw();
	}

#ifdef _DEBUG
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	pDevice->SetRenderState(D3DRS_ZENABLE, false);
	collider->Draw();
	pDevice->SetRenderState(D3DRS_ZENABLE, true);
#endif
}

/**************************************
�����蔻��`�揈��
***************************************/
void PlayerActor::DrawCollider()
{
	if (!active)
		return;

	colliderViewer->Draw();

	if(shield->IsActive())
		shield->Draw();
}

/**************************************
���x���A�b�v����
***************************************/
void PlayerActor::PowerUp()
{
	const int MaxLevel = 3;
	if (currentLevel >= MaxLevel)
		return;

	++currentLevel;

	for (auto&& turret : turretContainer)
	{
		turretRoot->RemoveChild(turret);
		ObjectPool::Instance()->Destroy<PlayerTurretActor>(turret);
	}
	turretContainer.clear();

	const float TurretOffset = 7.5f;
	const float PositionTurret = -2.0f;
	const int NumTurret[MaxLevel + 1]
	{
		2,
		4,
		6,
		8
	};
	int numTurret = NumTurret[currentLevel];

	D3DXVECTOR3 offset = { 0.0f, TurretOffset, PositionTurret };
	D3DXMATRIX mtxRot;
	D3DXMatrixRotationAxis(&mtxRot, &Vector3::Forward, D3DXToRadian(360.0f / numTurret));

	for (int i = 0; i < numTurret; i++)
	{
		PlayerTurretActor *turret = ObjectPool::Instance()->Create<PlayerTurretActor>();
		turretRoot->AddChild(turret);

		turret->SetLocalPosition(offset);
		D3DXVec3TransformCoord(&offset, &offset, &mtxRot);

		turret->Init();

		turretContainer.push_back(turret);
	}
}

/**************************************
���G����
***************************************/
bool PlayerActor::IsInvincivle() const
{
	return isInvincible;
}

/**************************************
���x���擾
***************************************/
int PlayerActor::PowerLevel()
{
	return currentLevel;
}

/**************************************
�ړ�����
***************************************/
void PlayerActor::_Move(const D3DXVECTOR3 & dir)
{
	if (!enableMove)
		return;

	D3DXVECTOR3 position = transform->GetPosition() + Vector3::Normalize(dir) * SpeedMove * FixedTime::GetTimeScale();

	position = Vector3::Clamp(-BorderMove, BorderMove, position);

	transform->SetPosition(position);
}

/**************************************
��]����
***************************************/
void PlayerActor::_Rotate(float dir)
{
	if (!enableMove)
		return;

	float targetAngle = dir * MaxAngle;
	float currentAngle = transform->GetEulerAngle().z;

	if (currentAngle >= 180.0f)
		currentAngle -= 360.0f;

	float rotAngle = (targetAngle - currentAngle) * 0.075f;

	transform->Rotate(rotAngle * FixedTime::GetTimeScale(), Vector3::Forward);
}

/**************************************
�V���b�g���ˏ���
***************************************/
void PlayerActor::_Shot()
{
	if (!enableShot)
		return;

	const float ShotInterval = 3.0f;
	cntShotFrame += FixedTime::GetTimeScale();

	if (cntShotFrame < ShotInterval)
		return;

	if (!GameInput::GetShotButtonPress())
		return;

	for (auto&& turret : turretContainer)
	{
		onFireBullet(turret->GetShotPosition(), false, currentLevel);
	}

	onFireBullet(transform->GetPosition() + ShotPosition, true, currentLevel);

	cntShotFrame = 0.0f;
}

/**************************************
�G�e�̌�������
***************************************/
void PlayerActor::_SlowDownEnemyBullet()
{
	if (!enableShot)
	{
		onSlowdownEnemyBullet(false);
		return;
	}

	bool input = GameInput::GetSlowdownButtonPress();
	onSlowdownEnemyBullet(input);
}

/**************************************
�{���o�[����
***************************************/
void PlayerActor::_FireBomber()
{
	if (!enableShot)
		return;

	if(GameInput::GetBomberButtonTrigger())
		onFireBomber();
}

/**************************************
�����蔻�菈��
***************************************/
void PlayerActor::OnColliderHit(ColliderObserver * other)
{
	onColliderHit(other);

	const std::string tag = other->Tag();
	if (tag == "EnemyBullet" || tag == "Enemy")
	{
		if (!isInvincible)
		{
			collider->SetActive(false);
			enableMove = false;
			enableShot = false;
			isInvincible = true;
		}
	}
}

/**************************************
�������̈ړ��I���R�[���o�b�N
***************************************/
void PlayerActor::OnFinishInitMove()
{
	collider->SetActive(true);
	enableMove = true;
	enableShot = true;

	TaskManager::Instance()->CreateDelayedTask(300.0f, false, [this]()
	{
		shield->SetActive(false);
		isInvincible = false;
	});
}
