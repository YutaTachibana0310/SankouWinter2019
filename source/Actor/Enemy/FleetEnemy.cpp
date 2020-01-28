//=====================================
//
// FleetEnemy.cpp
// �@�\:
// Author:GP12B332 21 ���ԗY��
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
�O���[�o���ϐ�
***************************************/

/**************************************
�R���X�g���N�^
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
�f�X�g���N�^
***************************************/
FleetEnemy::~FleetEnemy()
{
	shotTransform.reset();
	Utility::DeleteContainer(fsm);
}

/**************************************
����������
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
�I������
***************************************/
void FleetEnemy::Uninit()
{
	BaseBigEnemy::Uninit();

	SetCollider(false);
	active = false;
	ObjectPool::Instance()->Destroy<FleetEnemy>(this);
}

/**************************************
�X�V����
***************************************/
void FleetEnemy::Update()
{
	fsm[state]->OnUpdate(*this);
}

/**************************************
�`�揈��
***************************************/
void FleetEnemy::Draw()
{
	transform->SetWorld();
	mesh->Draw();

	colliders[0]->Draw();
}

/**************************************
�X�e�[�g�J��
***************************************/
void FleetEnemy::ChangeState(int next)
{
	state = FleetState(next);
	fsm[state]->OnStart(*this);
}
