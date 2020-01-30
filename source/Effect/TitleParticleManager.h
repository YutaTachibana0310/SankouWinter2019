//=====================================
//
//TitleParticleManager.h
//�@�\:�^�C�g���p�[�e�B�N���}�l�[�W��
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _TITLEPARTICLEMANAGER_H_
#define _TITLEPARTICLEMANAGER_H_

#include "../../main.h"
#include "../../Framework/Particle/SceneParticleManager.h"
#include "../../Framework/Pattern/BaseSingleton.h"

/**************************************
�O���錾
***************************************/
namespace TitleEffect
{
	enum ParticleID
	{
		PlayerTrail,
		//Speed,
		Max
	};
}

/**************************************
�N���X��`
***************************************/
class TitleParticleManager : public SceneParticleManager, public BaseSingleton<TitleParticleManager>
{
public:
	void Init();

};

#endif