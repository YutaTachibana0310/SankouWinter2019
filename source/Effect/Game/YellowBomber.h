//=====================================
//
//YellowBomber.h
//機能:イエローボンバー
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _YELLOWOBOMBER_H_
#define _YELLOWOBOMBER_H_

#include "../../../main.h"
#include "../../../Framework/Particle/BaseParticleController.h"
#include "../../../Framework/Particle/3D/AnimationParticle3D.h"

namespace Effect::Game
{
	/**************************************
	YellowBomberController
	***************************************/
	class YellowBomberController : public BaseParticleController
	{
	public:
		YellowBomberController();
	};

	/**************************************
	YellowBomber
	***************************************/
	class YellowBomber : public AnimationParticle3D
	{
	public:
		YellowBomber();

		void Init();
		void Update();

	private:
		float scale;
	};
}
#endif