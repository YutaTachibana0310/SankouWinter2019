//=====================================
//
//EnemyBulletVanish.h
//�@�\:�G�l�~�[�o���b�g�����G�t�F�N�g
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _ENEMYBULLETVANISH_H_
#define _ENEMYBULLETVANISH_H_

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
	�N���X��`
	***************************************/
	class EnemyBulletVanishController : public BaseParticleController
	{
	public:
		EnemyBulletVanishController();
	};

	/**************************************
	EnemyBulletVanish
	***************************************/
	class EnemyBulletVanish : public Particle3D
	{
	public:
		EnemyBulletVanish();

		void Init();
		void Update();

	private :
		D3DXVECTOR3 moveDir;
		float speed;

		float initScale;
	};

	/**************************************
	EnemyBulletVanishEmitter
	***************************************/
	class EnemyBulletVanishEmitter : public Enemy::EnemyParticleEmitter
	{
	public:
		EnemyBulletVanishEmitter();
	};
}


#endif