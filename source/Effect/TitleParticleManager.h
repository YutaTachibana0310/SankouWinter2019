//=====================================
//
//TitleParticleManager.h
//機能:タイトルパーティクルマネージャ
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _TITLEPARTICLEMANAGER_H_
#define _TITLEPARTICLEMANAGER_H_

#include "../../main.h"
#include "../../Framework/Particle/SceneParticleManager.h"
#include "../../Framework/Pattern/BaseSingleton.h"

/**************************************
前方宣言
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
クラス定義
***************************************/
class TitleParticleManager : public SceneParticleManager, public BaseSingleton<TitleParticleManager>
{
public:
	void Init();

};

#endif