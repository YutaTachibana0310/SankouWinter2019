//=====================================
//
// MiddleWayEnemy.cpp
// 機能:中型ウェイエネミー
// Author:GP12B332 21 立花雄太
//
//=====================================
#include "MiddleWayEnemy.h"
#include "../../../Framework/Renderer3D/MeshContainer.h"
#include "../../../Framework/Collider/BoxCollider3D.h"
#include "../../../Framework/Resource/ResourceManager.h"
#include "../../../Framework/Core/ObjectPool.h"

#include "../../System/EnemyTween.h"

/**************************************
グローバル変数
***************************************/

/**************************************
コンストラクタ
***************************************/
MiddleWayEnemy::MiddleWayEnemy(EnemyEventHandler * handle) :
	BaseMiddleEnemy(handle)
{
	ResourceManager::Instance()->GetMesh("DemoEnemy", mesh);

	colliders.resize(1, nullptr);
	colliders[0] = BoxCollider3D::Create("Enemy", transform);
	colliders[0]->AddObserver(this);
	colliders[0]->SetSize({ 5.0f, 8.0f, 7.0f });

	shotTransform = std::make_shared<Transform>();

	transform->AddChild(shotTransform);

	const D3DXVECTOR3 ShotPosition = { 0.0f, 0.0f, -5.0f };
	shotTransform->SetLocalPosition(ShotPosition);


}

/**************************************
デストラクタ
***************************************/
MiddleWayEnemy::~MiddleWayEnemy()
{
	shotTransform.reset();
	Utility::DeleteContainer(fsm);
}

/**************************************
初期化処理
***************************************/
void MiddleWayEnemy::Init()
{
	SetCollider(true);
	active = true;

	ChangeState(InitState);
}

/**************************************
終了処理
***************************************/
void MiddleWayEnemy::Uninit()
{
	SetCollider(false);
	active = false;
	ObjectPool::Instance()->Destroy<MiddleWayEnemy>(this);
}

/**************************************
更新処理
***************************************/
void MiddleWayEnemy::Update()
{
	fsm[state]->OnUpdate(*this);
}

/**************************************
描画処理
***************************************/
void MiddleWayEnemy::Draw()
{
	transform->SetWorld();
	mesh->Draw();
}

/**************************************
ステート遷移
***************************************/
void MiddleWayEnemy::ChangeState(int next)
{
	state = State(next);
	fsm[state]->OnStart(*this);
}
