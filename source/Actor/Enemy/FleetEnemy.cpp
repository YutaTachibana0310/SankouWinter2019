//=====================================
//
// FleetEnemy.cpp
// 機能:
// Author:GP12B332 21 立花雄太
//
//=====================================
#include "FleetEnemy.h"
#include "../../../Framework/Renderer3D/MeshContainer.h"
#include "../../../Framework/Collider/BoxCollider3D.h"
#include "../../../Framework/Resource/ResourceManager.h"
#include "../../../Framework/Core/ObjectPool.h"

#include "../../System/EnemyTween.h"
#include "../../Effect/GameParticleManager.h"

#include "State/FleetInit.h"
#include "State/FleetWait.h"
#include "State/FleetAttack.h"
#include "State/FleetInsanity.h"
#include "State/FleetEscape.h"

/**************************************
グローバル変数
***************************************/

/**************************************
コンストラクタ
***************************************/
FleetEnemy::FleetEnemy(EnemyEventHandler* handler) :
	BaseBigEnemy(handler)
{	
	ResourceManager::Instance()->GetMesh("FleetEnemy", mesh);

	colliders.reserve(0);
	colliders.push_back(BoxCollider3D::Create("Enemy", transform));
	colliders[0]->SetSize({ 5.0f, 10.0f, 10.0f });
	colliders[0]->AddObserver(this);

	shotTransform = std::make_shared<Transform>();
	transform->AddChild(shotTransform);

	fsm.resize(StateMax, nullptr);
	fsm[InitState] = new FleetInit();
	fsm[WaitState] = new FleetWait();
	fsm[AttackState] = new FleetAttack();
	fsm[InsanityState] = new FleetInsanity();
	fsm[EscapeState] = new FleetEscape();
}

/**************************************gae
デストラクタ
***************************************/
FleetEnemy::~FleetEnemy()
{
	shotTransform.reset();
	Utility::DeleteContainer(fsm);
}

/**************************************
初期化処理
***************************************/
void FleetEnemy::Init()
{
	active = true;
	SetCollider(true);

	hp = 300.0f;

	isDestroied = false;

	ChangeState(InitState);
}

/**************************************
終了処理
***************************************/
void FleetEnemy::Uninit()
{
	BaseBigEnemy::Uninit();

	SetCollider(false);
	active = false;
	ObjectPool::Instance()->Destroy<FleetEnemy>(this);
}

/**************************************
更新処理
***************************************/
void FleetEnemy::Update()
{
	fsm[state]->OnUpdate(*this);
}

/**************************************
描画処理
***************************************/
void FleetEnemy::Draw()
{
	transform->SetWorld();
	mesh->Draw();

	colliders[0]->Draw();
}

/**************************************
ステート遷移
***************************************/
void FleetEnemy::ChangeState(int next)
{
	state = FleetState(next);
	fsm[state]->OnStart(*this);
}
