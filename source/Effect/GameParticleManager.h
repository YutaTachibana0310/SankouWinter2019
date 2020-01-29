//=====================================
//
//GameParticleManager.h
//機能:ゲームパーティクルマネージャ
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _GAMEPARTICLEMANAGER_H_
#define _GAMEPARTICLEMANAGER_H_

#include "../../main.h"
#include "../../Framework/Particle/SceneParticleManager.h"
#include "../../Framework/Pattern/BaseSingleton.h"

/**************************************
前方宣言
***************************************/
namespace GameEffect
{
	enum ParticleID
	{
		PlayerBulletHit,
		EnemyExplosion,
		EnemyDebris,
		PlayerExplosion,
		EnemyFlame,
		EnemySmallDebris,
		EnemyBulletVanish,
		EnemyTrail,
		PlayerTrail,
		EnergyEffect,
		Max
	};
}

/**************************************
クラス定義
***************************************/
class GameParticleManager : public SceneParticleManager, public BaseSingleton<GameParticleManager>
{
public:
	void Init() override;
	void Update() override;

	void GenerateEnemyExplosion(const D3DXVECTOR3& position);
	void GenerateEnemySmallExplositon(const D3DXVECTOR3& position);
	void GenerateEnemyBigExplosion(const D3DXVECTOR3& position);

private:
	static const float BloomPower[3];
	static const float BloomThrethold[3];
};
#endif