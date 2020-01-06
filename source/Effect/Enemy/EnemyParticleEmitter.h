//=====================================
//
//EnemyParticleEmitter.h
//機能:エネミーのパーティクルエミッタ
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _ENEMYPARTICLEEMITTER_H_
#define _ENEMYPARTICLEEMITTER_H_

#include "../../../main.h"
#include "../../../Framework/Particle/BaseEmitter.h"

namespace Effect::Enemy
{
	/**************************************
	EnemyParticleEmitter
	***************************************/
	class EnemyParticleEmitter : public BaseEmitter
	{
		using BaseEmitter::BaseEmitter;

	public:
		virtual void Update() override;
	};
}


#endif