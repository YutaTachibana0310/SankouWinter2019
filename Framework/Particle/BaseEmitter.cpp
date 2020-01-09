//=====================================
//
//ベースエミッタ処理[BaseEmitter.cpp]
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "BaseEmitter.h"
#include "BaseParticle.h"
#include "../Camera/Camera.h"

/**************************************
マクロ定義
***************************************/

/**************************************
構造体定義
***************************************/

/**************************************
グローバル変数
***************************************/

/**************************************
コンストラクタ
***************************************/
BaseEmitter::BaseEmitter() :
	GameObject(false),
	emitNum(1),
	duration(1),
	useCull(false),
	isFinished(true),
	enableEmit(false),
	flgLoop(false),
	prevEmitTime(-1.0f)
{

}

/**************************************
コンストラクタ
***************************************/
BaseEmitter::BaseEmitter(int emitNum) :
	GameObject(false),
	emitNum(emitNum),
	duration(2),
	useCull(false),
	isFinished(true),
	enableEmit(false),
	flgLoop(false),
	prevEmitTime(-1.0f)
{

}

/**************************************
コンストラクタ
***************************************/
BaseEmitter::BaseEmitter(int emitNum, float duration) :
	GameObject(false),
	emitNum(emitNum),
	duration(duration),
	useCull(false),
	isFinished(true),
	enableEmit(false),
	flgLoop(false),
	prevEmitTime(-1.0f)
{

}

/**************************************
コンストラクタ
***************************************/
BaseEmitter::BaseEmitter(int emitNum, float durationMin, float durationMax) :
	GameObject(false),
	emitNum(emitNum),
	duration(Math::RandomRange(durationMin, durationMax)),
	useCull(false),
	isFinished(true),
	enableEmit(false),
	flgLoop(false),
	prevEmitTime(-1.0f)
{

}

/**************************************
コンストラクタ
***************************************/
BaseEmitter::BaseEmitter(int emitNumMin, int emitNumMax, float durationMin, float durationMax) :
	GameObject(false),
	emitNum(Math::RandomRange(emitNumMin, emitNumMax)),
	duration(Math::RandomRange(durationMin, durationMax)),
	useCull(false),
	isFinished(true),
	enableEmit(false),
	flgLoop(false),
	prevEmitTime(-1.0f)
{

}

/**************************************
デストラクタ
***************************************/
BaseEmitter::~BaseEmitter()
{

}

/**************************************
初期化処理
***************************************/
void BaseEmitter::Init(const std::function<void(void)>& callback)
{
	cntFrame = 0.0f;
	prevEmitTime = -1.0f;
	active = true;

	isFinished = false;
	enableEmit = true;

	this->callback = callback;

	for (auto&& particle : particleContainer)
	{
		particle->SetActive(false);
	}
}

/**************************************
更新処理
***************************************/
void BaseEmitter::Update()
{
	if (!active)
		return;

	cntFrame += FixedTime::GetTimeScale();

	Emit();

	UpdateParticle();

	CheckFinish();
}

/**************************************
放出処理
***************************************/
bool BaseEmitter::Emit()
{
	if (!enableEmit)
		return true;

	if (cntFrame < prevEmitTime)
		return true;

	prevEmitTime = ceilf(cntFrame);

	if (useCull)
	{
		D3DXVECTOR3 screenPos = Camera::MainCamera()->Projection(transform->GetPosition());
		if (screenPos.x < 0.0f || screenPos.x > SCREEN_WIDTH || screenPos.y < 0.0f || screenPos.y > SCREEN_HEIGHT)
			return true;
	}

	UINT cntEmit = 0;
	for (auto& particle : particleContainer)
	{
		if (particle->IsActive())
			continue;

		//初期化処理
		particle->SetTransform(*transform);
		particle->Init();

		//カウント
		cntEmit++;

		//決められ数だけ放出していたら終了
		if (cntEmit == emitNum)
			return true;
	}

	return false;
}

/**************************************
カリング使用設定
***************************************/
void BaseEmitter::UseCulling(bool value)
{
	useCull = value;
}

/**************************************
パーティクル更新処理
***************************************/
void BaseEmitter::UpdateParticle()
{
	isFinished = true;
	for (auto&& particle : particleContainer)
	{
		if (!particle->IsActive())
			continue;

		isFinished = false;

		particle->Update();
	}
}

/**************************************
終了確認
***************************************/
void BaseEmitter::CheckFinish()
{
	if (flgLoop)
		return;

	if (cntFrame < duration)
		return;

	enableEmit = false;

	if (!isFinished)
		return;

	active = false;

	if (callback != nullptr)
		callback();
}
