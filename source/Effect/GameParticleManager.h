//=====================================
//
//GameParticleManager.h
//�@�\:�Q�[���p�[�e�B�N���}�l�[�W��
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _GAMEPARTICLEMANAGER_H_
#define _GAMEPARTICLEMANAGER_H_

#include "../../main.h"
#include "../../Framework/Particle/SceneParticleManager.h"
#include "../../Framework/Pattern/BaseSingleton.h"

/**************************************
�O���錾
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
		Max
	};
}

namespace Effect::Game
{
	class EnergyEffectController;
	class ScoreEffectController;
}
class EnergyHandler;

/**************************************
�N���X��`
***************************************/
class GameParticleManager : public SceneParticleManager, public BaseSingleton<GameParticleManager>
{
public:
	void Init();
	void Uninit() override;
	void Update() override;

	void DrawEnergyEffect();

	void GenerateEnemyExplosion(const D3DXVECTOR3& position);
	void GenerateEnemySmallExplositon(const D3DXVECTOR3& position);
	void GenerateEnemyBigExplosion(const D3DXVECTOR3& position);
	void GenerateEnergyEffect(const D3DXVECTOR3& position, float energy);
	void GenerateScoreEffect(const D3DXVECTOR3& position, int point);

	void CreateEnergyEffectController(const std::shared_ptr<EnergyHandler>& energyHandler);

private:
	static const float BloomPower[3];
	static const float BloomThrethold[3];

	Effect::Game::EnergyEffectController *energyEffectController;
	Effect::Game::ScoreEffectController *scoreEffectController;
};
#endif