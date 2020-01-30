//=====================================
//
//TitlePlayerActor.cpp
//機能:プレイヤーアクター
//Author:GP12B332 21 立花雄太
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
staticメンバ
***************************************/

/**************************************
コンストラクタ
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
デストラクタ
***************************************/
TitlePlayerActor::~TitlePlayerActor()
{
	SAFE_DELETE(mesh);
}

/**************************************
初期化処理
***************************************/
void TitlePlayerActor::Init()
{
	active = true;

	transform->SetRotation(Quaternion::Identity);

	transform->SetPosition(Vector3::Zero);
	currentLevel = -1;
}

/**************************************
終了処理
***************************************/
void TitlePlayerActor::Uninit()
{
}

/**************************************
更新処理
***************************************/
void TitlePlayerActor::Update()
{
	if (!active)
		return;
}

/**************************************
描画処理
***************************************/
void TitlePlayerActor::Draw()
{
	if (!active)
		return;

	transform->SetWorld();
	mesh->Draw();
}