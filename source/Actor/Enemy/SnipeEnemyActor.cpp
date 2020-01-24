//=====================================
//
//SnipeEnemyActor.cpp
//�@�\:
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "SnipeEnemyActor.h"
#include "../../../Framework/Renderer3D/MeshContainer.h"
#include "../../../Framework/Collider/BoxCollider3D.h"
#include "../../../Framework/Resource/ResourceManager.h"
#include "../../../Framework/Core/ObjectPool.h"

#include "../../Handler/EnemyEventHandler.h"

#include "State\SnipeInit.h"
#include "State\SnipeAttack.h"
#include "State\SnipeEscape.h"

/**************************************
�O���[�o���ϐ�
***************************************/

/**************************************
�R���X�g���N�^
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

	fsm.resize(SnipeState::StateMax, nullptr);
	fsm[InitState] = new SnipeInit();
	fsm[AttackState] = new SnipeAttack();
	fsm[EscapeState] = new SnipeEscape();
}

/**************************************
�f�X�g���N�^
***************************************/
SnipeEnemyActor::~SnipeEnemyActor()
{
	shotTransform.reset();
	Utility::DeleteContainer(fsm);
}

/**************************************
����������
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
�I������
***************************************/
void SnipeEnemyActor::Uninit()
{
	SetCollider(false);
	active = false;
	ObjectPool::Instance()->Destroy<SnipeEnemyActor>(this);
}

/**************************************
�X�V����
***************************************/
void SnipeEnemyActor::Update()
{
	fsm[state]->OnUpdate(*this);
}

/**************************************
�`�揈��
***************************************/
void SnipeEnemyActor::Draw()
{
	transform->SetWorld();
	mesh->Draw();
}

/**************************************
�X�e�[�g�J��
***************************************/
void SnipeEnemyActor::ChangeState(int next)
{
	state = SnipeState(next);
	fsm[state]->OnStart(*this);
}

/**************************************
�v���C���[�̕�����������
***************************************/
void SnipeEnemyActor::LookAtPlayer()
{
	D3DXVECTOR3 diff = handle->GetPlayerPosition() - transform->GetPosition();
	transform->LookAt(transform->GetPosition() - diff);
}