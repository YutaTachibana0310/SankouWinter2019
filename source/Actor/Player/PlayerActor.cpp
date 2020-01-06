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
	cntShotFrame(0)
{
	mesh = new MeshContainer();
	turretTransform = new Transform();

	const unsigned MaxTurret = 4;
	turretContainer.reserve(MaxTurret);
	for (int i = 0; i < MaxTurret; i++)
	{
		turretContainer.push_back(new PlayerTurretActor());
		turretContainer[i]->Init(turretTransform);
	}

	const float PositionTurret = -2.0f;
	const float OffsetTurret = 5.0f;
	turretContainer[0]->SetPosition({ OffsetTurret, 0.0f, PositionTurret });
	turretContainer[1]->SetPosition({ -OffsetTurret, 0.0f, PositionTurret });
	turretContainer[2]->SetPosition({ 0.0f, OffsetTurret, PositionTurret });
	turretContainer[3]->SetPosition({ 0.0f, -OffsetTurret, PositionTurret });

	ResourceManager::Instance()->GetMesh("Player", mesh);
}

/**************************************
デストラクタ
***************************************/
PlayerActor::~PlayerActor()
{
	SAFE_DELETE(mesh);

	Utility::DeleteContainer(turretContainer);
}

/**************************************
初期化処理
***************************************/
void PlayerActor::Init()
{
	transform->SetPosition(Vector3::Zero);
}

/**************************************
終了処理
***************************************/
void PlayerActor::Uninit()
{
}

/**************************************
更新処理
***************************************/
void PlayerActor::Update()
{
	D3DXVECTOR3 direction = Vector3::Zero;
	direction.z = Input::GetPressHorizontail();
	direction.y = Input::GetPressVertical();

	_Move(direction);

	_Rotate(direction.y);

	const float AngleRotateTurret = 3.0f;
	turretTransform->Rotate(AngleRotateTurret * FixedTime::GetTimeScale(), Vector3::Forward);

	_Shot();

	Debug::Begin("Player");

	Debug::Text(transform->GetPosition(), "PlayerPos");
	Debug::End();
}

/**************************************
描画処理
***************************************/
void PlayerActor::Draw()
{
	transform->SetWorld();
	mesh->Draw();

	for (auto&& turret : turretContainer)
	{
		turret->Draw();
	}
}

/**************************************
移動処理
***************************************/
void PlayerActor::_Move(const D3DXVECTOR3 & dir)
{
	D3DXVECTOR3 position = transform->GetPosition() + Vector3::Normalize(dir) * SpeedMove * FixedTime::GetTimeScale();

	position = Vector3::Clamp(-BorderMove, BorderMove, position);

	transform->SetPosition(position);
	turretTransform->SetPosition(position);
}

/**************************************
回転処理
***************************************/
void PlayerActor::_Rotate(float dir)
{
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
