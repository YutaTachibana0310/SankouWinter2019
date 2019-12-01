#pragma once
//=====================================
//
//EnemyExplosion.h
//�@�\:�G�l�~�[����
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _ENEMYEXPLOSION_H_
#define _ENEMYEXPLOSION_H_

#include "../../../main.h"
#include "../../../Framework/Particle/BaseParticleController.h"
#include "../../../Framework/Particle/3D/AnimationParticle3D.h"

namespace Effect::Game
{
	/**************************************
	EnemyExplosionController
	***************************************/
	class EnemyExplosionController : public BaseParticleController
	{
	public:
		EnemyExplosionController();
	};

	/**************************************
	EnemyExplosion
	***************************************/
	class EnemyExplosion : public AnimationParticle3D
	{
	public:
		EnemyExplosion();

		void Init();
		void Update();

		static const float MaxSpeed;
		static const float MinSpeed;

	private:
		D3DXVECTOR3 moveDir;
		float initSpeed;
	};
}


#endif