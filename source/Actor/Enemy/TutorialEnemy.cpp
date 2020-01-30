//=====================================
//
//TutorialEnemyActor.cpp
//機能:
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "TutorialEnemy.h"
#include "../../../Framework/Resource/ResourceManager.h"
#include "../../../Framework/Renderer3D/MeshContainer.h"
#include "../../../Framework/Collider/BoxCollider3D.h"
#include "../../../Framework/Core/ObjectPool.h"
#include "../../../Framework/Particle/BaseEmitter.h"

#include "../../Effect/GameParticleManager.h"
#include "../../System/EnemyTween.h"
#include "../../Handler/EnemyEventHandler.h"
#include "../../Effect/GameParticleManager.h"
#include "../../Controller/EnemyTimeController.h"

/**************************************
コンストラクタ
***************************************/
TutorialEnemyActor::TutorialEnemyActor(EnemyEventHandler* handler) :
	BaseMiddleEnemy(handler),
	trailEmitterL(nullptr),
	trailEmitterR(nullptr)
{
	ResourceManager::Instance()->GetMesh("DemoEnemy", mesh);

	colliders.resize(1, nullptr);
	colliders[0] = BoxCollider3D::Create("Enemy", transform);
	colliders[0]->AddObserver(this);
	colliders[0]->SetSize({ 5.0f, 8.0f, 7.0f });

	shotTransformLeft = std::make_shared<Transform>();
	shotTransformRight = std::make_shared<Transform>();

	transform->AddChild(shotTransformLeft);
	transform->AddChild(shotTransformRight);

	const D3DXVECTOR3 ShotPositionLeft = { 0.0f, 2.0f, -5.0f };
	const D3DXVECTOR3 ShotPositionRight = { 0.0f, -2.0f, -5.0f };
	shotTransformLeft->SetLocalPosition(ShotPositionLeft);
	shotTransformRight->SetLocalPosition(ShotPositionRight);

	shotTransformLeft->Rotate(20.0f, Vector3::Right);
	shotTransformRight->Rotate(20.0f, Vector3::Left);
}

/**************************************
デストラクタ
***************************************/
TutorialEnemyActor::~TutorialEnemyActor()
{
	shotTransformLeft.reset();
	shotTransformRight.reset();
}

/**************************************
初期化処理
***************************************/
void TutorialEnemyActor::Init()
{
	SetCollider(true);
	active = true;
	enableAttack = false;

	cntFrame = 0;
	cntAttack = 0;

	trailEmitterL = GameParticleManager::Instance()->Generate(GameEffect::EnemyTrail, *transform);
	if (trailEmitterL != nullptr)
	{
		AddChild(trailEmitterL);
		trailEmitterL->SetLocalPosition({ 0.0f, 2.0f, 2.2f });
	}

	trailEmitterR = GameParticleManager::Instance()->Generate(GameEffect::EnemyTrail, *transform);
	if (trailEmitterR != nullptr)
	{
		AddChild(trailEmitterR);
		trailEmitterR->SetLocalPosition({ 0.0f, -2.0f, 2.2f });
	}

	hp = 100.0f;

	transform->SetPosition({ 0.0f, 0.0f, 60.0f });
	EnemyTween::Move(*this, { 0.0f, 0.0f, 30.0f }, 60.0f, EaseType::OutCubic, [this]()
	{
		enableAttack = true;
	});
}

/**************************************
終了処理
***************************************/
void TutorialEnemyActor::Uninit()
{
	if (trailEmitterL != nullptr)
	{
		RemoveChild(trailEmitterL);
		trailEmitterL->SetActive(false);
		trailEmitterL = nullptr;
	}

	if (trailEmitterR != nullptr)
	{
		RemoveChild(trailEmitterR);
		trailEmitterR->SetActive(false);
		trailEmitterR = nullptr;
	}

	Init();
}

/**************************************
更新処理
***************************************/
void TutorialEnemyActor::Update()
{
	if (!enableAttack)
		return;

	cntFrame += EnemyTimeController::GetTimeScale();

	const float Interval = 120.0f;
	if (enableAttack && cntFrame >= Interval * cntAttack)
	{
		handle->SetBullet(*shotTransformLeft, EnemyBulletConfig::BlueRotate, 0.3f);
		handle->SetBullet(*shotTransformRight, EnemyBulletConfig::RedRotate, 0.3f);

		++cntAttack;
	}
}

/**************************************
描画処理
***************************************/
void TutorialEnemyActor::Draw()
{
	transform->SetWorld();
	mesh->Draw();
}

/**************************************
ステート遷移
***************************************/
void TutorialEnemyActor::ChangeState(int next)
{
}
