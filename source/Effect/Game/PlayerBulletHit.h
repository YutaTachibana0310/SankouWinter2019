//=====================================
//
//PlayerBulletHit.h
//‹@”\:
//Author:GP12B332 21 —§‰Ô—Y‘¾
//
//=====================================
#ifndef _PLAYERBULLETHIT_H_
#define _PLAYERBULLETHIT_H_

#include "../../../main.h"
#include "../../../Framework/Particle/BaseParticleController.h"
#include "../../../Framework/Particle/3D/Particle3D.h"

namespace Effect::Game
{
	/**************************************
	PlayerBulletHitController
	***************************************/
	class PlayerBulletHitController : public BaseParticleController
	{
	public:
		PlayerBulletHitController();
	};

	/**************************************
	PlayerBulletHit
	***************************************/
	class PlayerBulletHit : public Particle3D
	{
	public:
		PlayerBulletHit();

		void Init();
		void Update();

	private:
		D3DXVECTOR3 moveDir;
		float initScale;
	};
}


#endif