//=====================================
//
//DemoEnemyActor.cpp
//�@�\:
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "DemoEnemyActor.h"
#include "../../../Framework/Resource/ResourceManager.h"
#include "../../../Framework/Renderer3D/MeshContainer.h"
#include "../../../Framework/Collider/BoxCollider3D.h"
#include "../../../Framework/Core/ObjectPool.h"

#include "../../Effect/GameParticleManager.h"
#include "../../System/EnemyTween.h"
#include "../../Handler/EnemyEventHandler.h"

#include "State\DemoInit.h"
#include "State\DemoAttack.h"
#include "State\DemoWait.h"
#include "State\DemoEscape.h"

/**************************************
�R���X�g���N�^
***************************************/
DemoEnemyActor::DemoEnemyActor(EnemyEventHandler* handler) :
	BaseMiddleEnemy(handler)
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

	fsm.resize(DemoState::MaxState, nullptr);
	fsm[InitState] = new DemoInit();
	fsm[AttackState] = new DemoAttack();
	fsm[WaitState] = new DemoWait();
	fsm[EscapeState] = new DemoEscape();
}

/**************************************
�f�X�g���N�^
***************************************/
DemoEnemyActor::~DemoEnemyActor()
{
	shotTransformLeft.reset();
	shotTransformRight.reset();

	Utility::DeleteContainer(fsm);
}

/**************************************
����������
***************************************/
void DemoEnemyActor::Init()
{
	SetCollider(true);
	active = true;

	cntFrame = 0;
	cntAttack = 0;
	ChangeState(InitState);

	hp = 70.0f;
}

/**************************************
�I������
***************************************/
void DemoEnemyActor::Uninit()
{
	SetCollider(false);
	active = false;
	ObjectPool::Instance()->Destroy<DemoEnemyActor>(this);
}

/**************************************
�X�V����
***************************************/
void DemoEnemyActor::Update()
{
	D3DXVECTOR3 diff = handle->GetPlayerPosition() - transform->GetPosition();
	transform->LookAt(transform->GetPosition() - diff);

	fsm[state]->OnUpdate(*this);
}

/**************************************
�`�揈��
***************************************/
void DemoEnemyActor::Draw()
{
	transform->SetWorld();
	mesh->Draw();
}

/**************************************
�X�e�[�g�J��
***************************************/
void DemoEnemyActor::ChangeState(int next)
{
	state = DemoState(next);
	fsm[state]->OnStart(*this);
}
