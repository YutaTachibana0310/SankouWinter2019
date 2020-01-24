//=====================================
//
//SnipeEnemyActor.cpp
//機能:
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "SnipeEnemyActor.h"
#include "../../../Framework/Renderer3D/MeshContainer.h"
#include "../../../Framework/Collider/BoxCollider3D.h"
#include "../../../Framework/Resource/ResourceManager.h"
#include "../../../Framework/Core/ObjectPool.h"

#include "../../Handler/EnemyEventHandler.h"

/**************************************
グローバル変数
***************************************/

/**************************************
コンストラクタ
***************************************/
SnipeEnemyActor::SnipeEnemyActor(EnemyEventHandler * handler) :
	BaseSmallEnemy(handler),
	cntFrame(0.0f),
	cntAttack(0),
	enableSnipe(true)
{
	colliders.reserve(1);
	colliders.push_back(BoxCollider3D::Create("Enemy", transform));
	colliders[0]->SetSize({ 5.0f, 2.0f, 2.0f });
	colliders[0]->AddObserver(this);

	ResourceManager::Instance()->GetMesh("RotateEnemy", mesh);

	shotTransform = std::make_shared<Transform>();
	transform->AddChild(shotTransform);
	shotTransform->SetLocalPosition({ 0.0f, 0.0f, -2.0f });

}

/**************************************
デストラクタ
***************************************/
SnipeEnemyActor::~SnipeEnemyActor()
{
	shotTransform.reset();
}

/**************************************
初期化処理
***************************************/
void SnipeEnemyActor::Init()
{
	cntFrame = 0.0f;
	cntAttack = 0;
	active = true;
	SetCollider(true);

	hp = 5.0f;

	ChangeState(InitState);
}

/**************************************
終了処理
***************************************/
void SnipeEnemyActor::Uninit()
{
	SetCollider(false);
	active = false;
	ObjectPool::Instance()->Destroy<SnipeEnemyActor>(this);
}

/**************************************
更新処理
***************************************/
void SnipeEnemyActor::Update()
{
	fsm[state]->OnUpdate(*this);
}

/**************************************
描画処理
***************************************/
void SnipeEnemyActor::Draw()
{
	transform->SetWorld();
	mesh->Draw();
}

/**************************************
ステート遷移
***************************************/
void SnipeEnemyActor::ChangeState(int next)
{
	state = SnipeState(next);
	fsm[state]->OnStart(*this);
}
