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
更新処理
***************************************/
void Effect::Enemy::EnemyParticleEmitter::Update()
{
	if (!active)
		return;

	cntFrame += EnemyTimeController::GetTimeScale();

	Emit();

	UpdateParticle();

	CheckFinish();
}