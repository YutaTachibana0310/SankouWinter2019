//=====================================
//
//EnemyParticleEmitter.cpp
//機能:エネミーのパーティクルエミッタ
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "EnemyParticleEmitter.h"
#include "../../Controller/EnemyTimeController.h"

/**************************************
初期化処理
***************************************/
void Effect::Enemy::EnemyParticleEmitter::Init(std::function<void()>& callback)
{
	prevEmit = 0.0f;
	BaseEmitter::Init(callback);
}

/**************************************
更新処理
***************************************/
void Effect::Enemy::EnemyParticleEmitter::Update()
{
	if (!IsActive())
		return;

	cntFrame += EnemyTimeController::GetTimeScale();

	if (cntFrame >= duration && callback != nullptr)
	{
		callback();
	}
}

/**************************************
放出処理
***************************************/
bool Effect::Enemy::EnemyParticleEmitter::Emit(std::vector<BaseParticle*>& container)
{
	if (cntFrame < prevEmit)
		return true;

	prevEmit = floorf(cntFrame);
	return BaseEmitter::Emit(container);
}
