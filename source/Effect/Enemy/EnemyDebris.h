//=====================================
//
// EnemyDebris.h
// �@�\:�G�l�~�[�̔����j��
// Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _ENEMYDEBRIS_H_
#define _ENEMYDEBRIS_H_

#include "../../../main.h"
#include "../../../Framework/Particle/BaseParticleController.h"
#include "../../../Framework/Particle/3D/Particle3D.h"
#include "EnemyParticleEmitter.h"

namespace Effect::Game
{
	/**************************************
	�O���錾
	***************************************/

	/**************************************
	EnemyDebrisController
	***************************************/
	class EnemyDebrisController : public BaseParticleController
	{
	public:
		EnemyDebrisController();
	};

	/**************************************
	EnemyDebris
	***************************************/
	class EnemyDebris : public Particle3D
	{
	public:
		EnemyDebris();

		void Init();
		void Update();

	private:
		D3DXVECTOR3 moveDir;
		float speed;
	};

	/**************************************
	EnemyDebrisEmitter
	***************************************/
	class EnemyDebrisEmitter : public Enemy::EnemyParticleEmitter
	{
	public:
		EnemyDebrisEmitter();
	};
}
#endif