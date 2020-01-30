//=====================================
//
//YellowSpark.h
//機能:イエロースパーク
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _YELLOWSPARK_H_
#define _YELLOWSPARK_H_

#include "../../../main.h"
#include "../../../Framework/Particle/3D/Particle3D.h"
#include "../../../Framework/Particle/BaseParticleController.h"

/**************************************
前方宣言
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