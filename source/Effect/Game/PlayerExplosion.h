//=====================================
//
// PlayerExplosion.h
// 機能:プレイヤー爆発エフェクト
// Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _PLAYEREXPLOSION_H_
#define _PLAYEREXPLOSION_H_

#include "../../../main.h"
#include "../../../Framework/Particle/BaseParticleController.h"
#include "../../../Framework/Particle/3D/AnimationParticle3D.h"

/**************************************
前方宣言
***************************************/

namespace Effect::Game
{
	/**************************************
	PlayerExplosionControllerクラス
	***************************************/
	class PlayerExplosionController : public BaseParticleController
	{
	public:
		PlayerExplosionController();
	};

	/**************************************
	PlayerExplosionクラス
	***************************************/
	class PlayerExplosion : public AnimationParticle3D
	{
	public:
		PlayerExplosion();

		void Init();
		void Update();

	private:
		D3DXVECTOR3 moveDir;
		float speed;
		float initScale;
	};
}
#endif