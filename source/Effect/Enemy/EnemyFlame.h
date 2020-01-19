//=====================================
//
// EnemyFlame.h
// 機能:エネミー爆炎エフェクト
// Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _ENEMYFLAME_H_
#define _ENEMYFLAME_H_

#include "../../../main.h"
#include "../../../Framework/Particle/BaseParticleController.h"
#include "../../../Framework/Particle/3D/AnimationParticle3D.h"
#include "EnemyParticleEmitter.h"

namespace Effect::Game
{
	/**************************************
	EnemyFlameController
	***************************************/
	class EnemyFlameController : public BaseParticleController
	{
	public:
		EnemyFlameController();
	};

	/**************************************
	EnemyFlame
	***************************************/
	class EnemyFlame : public AnimationParticle3D
	{
	public:
		EnemyFlame();

		void Init();
		void Update();

		static const float MaxSpeed;
		static const float MinSpeed;
		static const D3DXVECTOR3 RangeOffset;

	private:
		D3DXVECTOR3 moveDir;
		float initSpeed;
	};

	/**************************************
	EnemyFlameEmitter
	***************************************/
	class EnemyFlameEmitter : public Enemy::EnemyParticleEmitter
	{
	public:
		EnemyFlameEmitter();
	};
}


#endif