//=====================================
//
// MiddleWayEnemy.cpp
// �@�\:���^�E�F�C�G�l�~�[
// Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "MiddleWayEnemy.h"
#include "../../../Framework/Renderer3D/MeshContainer.h"
#include "../../../Framework/Collider/BoxCollider3D.h"
#include "../../../Framework/Resource/ResourceManager.h"
#include "../../../Framework/Core/ObjectPool.h"

#include "../../System/EnemyTween.h"

#include "State/MiddleWayAttack.h"
#include "State/MiddleWayEscape.h"
#include "State/MiddleWayInit.h"

/**************************************
�O���[�o���ϐ�
***************************************/

/**************************************
�R���X�g���N�^
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

	fsm.resize(State::StateMax, nullptr);
	fsm[State::InitState] = new MiddleWayInit();
	fsm[State::AttackState] = new MiddleWayAttack();
	fsm[State::EscapeState] = new MiddleWayEscape();
}

/**************************************
�f�X�g���N�^
***************************************/
MiddleWayEnemy::~MiddleWayEnemy()
{
	shotTransform.reset();
	Utility::DeleteContainer(fsm);
}

/**************************************
����������
***************************************/
void MiddleWayEnemy::Init()
{
	SetCollider(true);
	active = true;

	hp = 50.0f;

	ChangeState(InitState);
}

/**************************************
�I������
***************************************/
void MiddleWayEnemy::Uninit()
{
	SetCollider(false);
	active = false;
	ObjectPool::Instance()->Destroy<MiddleWayEnemy>(this);
}

/**************************************
�X�V����
***************************************/
void MiddleWayEnemy::Update()
{
	fsm[state]->OnUpdate(*this);
}

/**************************************
�`�揈��
***************************************/
void MiddleWayEnemy::Draw()
{
	transform->SetWorld();
	mesh->Draw();
}

/**************************************
�X�e�[�g�J��
***************************************/
void MiddleWayEnemy::ChangeState(int next)
{
	state = State(next);
	fsm[state]->OnStart(*this);
}