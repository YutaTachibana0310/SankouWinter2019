//=====================================
//
// PlayerExplosion.h
// �@�\:�v���C���[�����G�t�F�N�g
// Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _PLAYEREXPLOSION_H_
#define _PLAYEREXPLOSION_H_

#include "../../../main.h"
#include "../../../Framework/Particle/BaseParticleController.h"
#include "../../../Framework/Particle/3D/AnimationParticle3D.h"

/**************************************
�O���錾
***************************************/

namespace Effect::Game
{
	/**************************************
	PlayerExplosionController�N���X
	***************************************/
	class PlayerExplosionController : public BaseParticleController
	{
	public:
		PlayerExplosionController();
	};

	/**************************************
	PlayerExplosion�N���X
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