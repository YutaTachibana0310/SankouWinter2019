//=====================================
//
//TitlePlayerActor.cpp
//�@�\:�v���C���[�A�N�^�[
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "TitlePlayerActor.h"
#include "../../../Framework/Renderer3D/MeshContainer.h"
#include "../../../Framework/Resource/ResourceManager.h"
#include "../../../Framework/Input/input.h"
#include "../../../Framework/Tool/DebugWindow.h"
#include "../../../Framework/Core/ObjectPool.h"
#include "../../../Framework/Collider/BoxCollider3D.h"
#include "../../../Framework/Tween/Tween.h"
#include "../../../Framework/Core/ObjectPool.h"
#include "../../../Framework/Particle/BaseEmitter.h"

#include "../../Effect/TitleParticleManager.h"

/**************************************
static�����o
***************************************/

/**************************************
�R���X�g���N�^
***************************************/
TitlePlayerActor::TitlePlayerActor() :
	cntShotFrame(0),
	enableShot(false),
	enableMove(false),
	currentLevel(0),
	trailEmitter(nullptr)
{
	mesh = new MeshContainer();
	ResourceManager::Instance()->GetMesh("Player", mesh);

	trailEmitter = TitleParticleManager::Instance()->Generate(TitleEffect::PlayerTrail, *transform);
	AddChild(trailEmitter);
	trailEmitter->SetLocalPosition(Vector3::Back * 2.2f);
	trailEmitter->SetScale(Vector3::One * 0.2f);
	
	transform->SetPosition({ 0.0f, -5.0f, -30.0f });
}

/**************************************
�f�X�g���N�^
***************************************/
TitlePlayerActor::~TitlePlayerActor()
{
	SAFE_DELETE(mesh);
}

/**************************************
����������
***************************************/
void TitlePlayerActor::Init()
{
	active = true;

	transform->SetRotation(Quaternion::Identity);

	transform->SetPosition(Vector3::Zero);
	currentLevel = -1;
}

/**************************************
�I������
***************************************/
void TitlePlayerActor::Uninit()
{
}

/**************************************
�X�V����
***************************************/
void TitlePlayerActor::Update()
{
	if (!active)
		return;
}

/**************************************
�`�揈��
***************************************/
void TitlePlayerActor::Draw()
{
	if (!active)
		return;

	transform->SetWorld();
	mesh->Draw();
}