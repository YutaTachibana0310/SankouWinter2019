//=====================================
//
// EnemySmallDebris.h
// ‹@”\:
// Author:GP12B332 21 —§‰Ô—Y‘¾
//
//=====================================
#ifndef _ENEMYSMALLDEBRIS_H_
#define _ENEMYSMALLDEBRIS_H_

#include "../../../main.h"
#include "../../../Framework/Particle/3D/Particle3D.h"
#include "../../../Framework/Particle/BaseParticleController.h"
#include "EnemyParticleEmitter.h"

namespace Effect::Game
{
	/**************************************
	EnemySmallDebrisController
	***************************************/
	class EnemySmallDebrisController : public BaseParticleController
	{
	public:
		EnemySmallDebrisController();
	};

	/**************************************
	EnemySmallDebris
	***************************************/
	class EnemySmallDebris : public Particle3D
	{
	public:
		EnemySmallDebris();
		
		void Init();
		void Update();

		static const float MaxSpeed;
		static const float MinSpeed;

	private:
		D3DXVECTOR3 moveDir;
		float initSpeed;
	};

	/**************************************
	EnemySmallDebrisEmitter
	***************************************/
	class EnemySmallDebirsEmitter : public Enemy::EnemyParticleEmitter
	{
	public:
		EnemySmallDebirsEmitter();
	};
}



#endif