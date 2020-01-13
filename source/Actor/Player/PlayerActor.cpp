//=====================================
//
//PlayerActor.cpp
//機能:プレイヤーアクター
//Author:GP12B332 21 立花雄太
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

#include "PlayerTurretActor.h"
#include "PlayerBulletActor.h"

/**************************************
staticメンバ
***************************************/
const float PlayerActor::SpeedMove = 0.6f;
const D3DXVECTOR3 PlayerActor::BorderMove = { 0.0f, 25.0f, 45.0f };
const float PlayerActor::MaxAngle = 40.0f;

/**************************************
コンストラクタ
***************************************/
PlayerActor::PlayerActor() :
	cntShotFrame(0),
	enableShot(false),
	enableMove(false)
{
	mesh = new MeshContainer();
	ResourceManager::Instance()->GetMesh("Player", mesh);

	turretRoot = new PlayerTurretRoot();
	AddChild(turretRoot);
	turretRoot->SetLocalPosition(Vector3::Zero);

	collider = BoxCollider3D::Create("Player", transform);
	collider->SetSize({ 0.5f, 0.5f, 0.5f });
	collider->AddObserver(this);

	const unsigned MaxTurret = 4;
	turretContainer.reserve(MaxTurret);
	for (int i = 0; i < MaxTurret; i++)
	{
		turretContainer.push_back(new PlayerTurretActor());
		turretRoot->AddChild(turretContainer[i]);
	}

	const float PositionTurret = -2.0f;
	const float OffsetTurret = 5.0f;
	turretContainer[0]->SetPosition({ OffsetTurret, 0.0f, PositionTurret });
	turretContainer[1]->SetPosition({ -OffsetTurret, 0.0f, PositionTurret });
	turretContainer[2]->SetPosition({ 0.0f, OffsetTurret, PositionTurret });
	turretContainer[3]->SetPosition({ 0.0f, -OffsetTurret, PositionTurret });
}

/**************************************
デストラクタ
***************************************/
PlayerActor::~PlayerActor()
{
	SAFE_DELETE(mesh);
	SAFE_DELETE(turretRoot);
	collider.reset();
	Utility::DeleteContainer(turretContainer);
}

/**************************************
初期化処理
***************************************/
void PlayerActor::Init()
{
	active = true;

	transform->SetRotation(Quaternion::Identity);

	const D3DXVECTOR3 InitPos = { 0.0f, 0.0f, -55.0f };
	const D3DXVECTOR3 StartPos = { 0.0f, 0.0f, -20.0f };
	auto callback = std::bind(&PlayerActor::OnFinishInitMove, this);
	Tween::Move(*this, InitPos, StartPos, 60.0f, EaseType::OutBack, false, callback);
}

/**************************************
終了処理
***************************************/
void PlayerActor::Uninit()
{
	collider->SetActive(false);
	active = false;
}

/**************************************
更新処理
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

	turretRoot->Update();
	for (auto&& turret : turretContainer)
	{
		turret->Update();
	}

	Debug::Begin("Player");

	Debug::Text(transform->GetPosition(), "PlayerPos");
	Debug::Text(transform->GetScale(), "PlayerScale");
	Debug::Text(Quaternion::ToEuler(transform->GetRotation()), "PlayerRotation");
	Debug::Text(turretContainer[0]->GetPosition(), "Turretposition");
	Debug::End();
}

/**************************************
描画処理
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
移動処理
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
回転処理
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
ショット発射処理
***************************************/
void PlayerActor::_Shot()
{
	if (!enableShot)
		return;

	const float ShotInterval = 3.0f;

	cntShotFrame += FixedTime::GetTimeScale();
	
	if (cntShotFrame < ShotInterval)
		return;

	for (auto&& turret : turretContainer)
	{
		onFireBullet(turret->GetShotPosition());
	}

	cntShotFrame = 0.0f;
}

/**************************************
当たり判定処理
***************************************/
void PlayerActor::OnColliderHit(ColliderObserver * other)
{
	collider->SetActive(false);
	enableMove = false;
	enableShot = false;

	onColliderHit(other);
}

/**************************************
初期化の移動終了コールバック
***************************************/
void PlayerActor::OnFinishInitMove()
{
	collider->SetActive(true);
	enableMove = true;
	enableShot = true;
}
