//=====================================
//
//EnergyEffect.h
//機能:エナジーエフェクト
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _ENERGYEFFECT_H_
#define _ENERGYEFFECT_H_

#include "../../../main.h"
#include "../../../Framework/Particle/BaseParticleController.h"
#include "../../../Framework/Particle/2D/Particle2D.h"

namespace Effect::Game 
{
	/**************************************
	EnergyEffectController
	***************************************/
	class EnergyEffectController : public BaseParticleController
	{
	public:
		EnergyEffectController();
	};

	/**************************************
	EnergyEffect
	***************************************/
	class EnergyEffect : public Particle2D
	{
	public:
		EnergyEffect();

		void Init();
		void Update();

		void SetDirection(const D3DXVECTOR3& direction);

	private:
		D3DXVECTOR3 velocity;

		static const float LifeFrame;
	};

	/**************************************
	EnergyEffectEmitter
	***************************************/
	class EnergyEffectEmitter : public BaseEmitter
	{
	public:
		EnergyEffectEmitter();

		bool Emit() override;
	};
}
#endif