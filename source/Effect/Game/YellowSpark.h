//=====================================
//
//YellowSpark.h
//�@�\:�C�G���[�X�p�[�N
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _YELLOWSPARK_H_
#define _YELLOWSPARK_H_

#include "../../../main.h"
#include "../../../Framework/Particle/3D/Particle3D.h"
#include "../../../Framework/Particle/BaseParticleController.h"

/**************************************
�O���錾
***************************************/

namespace Effect::Game
{
	/**************************************
	YellowSparkController
	***************************************/
	class YellowSparkController : public BaseParticleController
	{
	public:
		YellowSparkController();
	};

	/**************************************
	YellowSpark
	***************************************/
	class YellowSpark : public Particle3D
	{
	public:
		YellowSpark();

		void Init();
		void Update();

	private:
		float initScale;
	};
}
#endif