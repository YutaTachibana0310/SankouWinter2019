//=====================================
//
//PlayerTrail.h
//�@�\:�v���C���[�g���C���G�t�F�N�g
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _PLAYERTRAIL_H_
#define _PLAYERTRAIL_H_

#include "../../../main.h"
#include "../../../Framework/Particle/BaseParticleController.h"
#include "../../../Framework/Particle/3D/Particle3D.h"

namespace Effect::Game 
{
	/**************************************
	PlayerTrailController
	***************************************/
	class PlayerTrailController : public BaseParticleController
	{
	public:
		PlayerTrailController();
	};

	/**************************************
	PlayerTrail
	***************************************/
	class PlayerTrail : public Particle3D
	{
	public:
		PlayerTrail();

		void Init();
		void Update();

	private:
		float initScale;
	};

	/**************************************
	PlayerTrailEmitter
	***************************************/
	class PlayerTrailEmitter : public BaseEmitter
	{
	public:
		PlayerTrailEmitter();
	};
}
#endif