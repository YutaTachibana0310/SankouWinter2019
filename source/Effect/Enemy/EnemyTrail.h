//=====================================
//
//EnemyTrail.h
//機能:エネミートレイルエフェクト
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _ENEMYTRAIL_H_
#define _ENEMYTRAIL_H_

#include "../../../main.h"
#include "../../../Framework/Particle/3D/Particle3D.h"
#include "../../../Framework/Particle/BaseParticleController.h"
#include "EnemyParticleEmitter.h"

namespace Effect::Game
{
	/**************************************
	EnemyTrailController
	***************************************/
	class EnemyTrailController : public BaseParticleController
	{
	public:
		EnemyTrailController();
	};

	/**************************************
	EnemyTrail
	***************************************/
	class EnemyTrail : public Particle3D
	{
	public:
		EnemyTrail();

		void Init();
		void Update();

	private:
		D3DXVECTOR3 moveDir;
		float initScale;
	};

	/**************************************
	EnemyTrailEmitter
	***************************************/
	class EnemyTrailEmitter : public Enemy::EnemyParticleEmitter
	{
	public:
		EnemyTrailEmitter();
	};
}
#endif