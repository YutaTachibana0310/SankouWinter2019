//=====================================
//
//EnemyParticleEmitter.h
//�@�\:�G�l�~�[�̃p�[�e�B�N���G�~�b�^
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _ENEMYPARTICLEEMITTER_H_
#define _ENEMYPARTICLEEMITTER_H_

#include "../../../main.h"
#include "../../../Framework/Particle/BaseEmitter.h"

namespace Effect::Enemy
{
	/**************************************
	EnemyParticleEmitter
	***************************************/
	class EnemyParticleEmitter : public BaseEmitter
	{
		using BaseEmitter::BaseEmitter;

	public:
		virtual void Init(std::function<void()>& callback);
		virtual void Update() override;
		virtual bool Emit(std::vector<BaseParticle*>& container);

	protected:
		float prevEmit;
	};
}


#endif