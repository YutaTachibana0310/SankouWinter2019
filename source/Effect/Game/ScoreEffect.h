//=====================================
//
//ScoreEffect.h
//機能:エナジーエフェクト
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _SCOREEFFECT_H_
#define _SCOREEFFECT_H_

#include "../../../main.h"
#include "../../../Framework/Particle/BaseParticleController.h"
#include "../../../Framework/Particle/2D/Particle2D.h"

class ScoreHandler;

namespace Effect::Game
{
	/**************************************
	ScoreEffectController
	***************************************/
	class ScoreEffectController : public BaseParticleController
	{
	public:
		ScoreEffectController();

		void SetEmitter(const D3DXVECTOR3& position, int point);
	};

	/**************************************
	ScoreEffect
	***************************************/
	class ScoreEffect : public Particle2D
	{
	public:
		ScoreEffect();
		~ScoreEffect();

		void Init();
		void Update();

		void SetDirection(const D3DXVECTOR3& direction);
		void SetScore(int point);

	private:
		D3DXVECTOR3 velocity;
		int point;

		static const float LifeFrame;
	};

	/**************************************
	ScoreEffectEmitter
	***************************************/
	class ScoreEffectEmitter : public BaseEmitter
	{
	public:
		ScoreEffectEmitter();

		bool Emit() override;
		void SetScore(int point);

	private:
		int point;
	};
}
#endif