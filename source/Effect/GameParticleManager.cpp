//=====================================
//
//GameParticleManager.cpp
//機能:ゲームパーティクルマネージャ
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "GameParticleManager.h"
#include "../../Framework/PostEffect/CrossFilterController.h"
#include "../../Framework/Tool/DebugWindow.h"
#include "../../Framework/Task/TaskManager.h"

#include "Game\PlayerBulletHit.h"
#include "Enemy\EnemyExplosion.h"
#include "Enemy/EnemyDebris.h"
#include "Game/PlayerExplosion.h"
#include "Enemy/EnemyFlame.h"
#include "Enemy/EnemySmallDebris.h"

/**************************************
staticメンバ
***************************************/
const float GameParticleManager::BloomPower[3] = { 1.0f, 1.0f, 1.0f };
const float GameParticleManager::BloomThrethold[3] = { 0.46f, 0.35f, 0.18f };

/**************************************
初期化処理
***************************************/
void GameParticleManager::Init()
{
	SceneParticleManager::Init();

	controllers.resize(GameEffect::Max);
	controllers[GameEffect::PlayerBulletHit] = new Effect::Game::PlayerBulletHitController();
	controllers[GameEffect::EnemyExplosion] = new Effect::Game::EnemyExplosionController();
	controllers[GameEffect::EnemyDebris] = new Effect::Game::EnemyDebrisController();
	controllers[GameEffect::PlayerExplosion] = new Effect::Game::PlayerExplosionController();
	controllers[GameEffect::EnemyFlame] = new Effect::Game::EnemyFlameController();
	controllers[GameEffect::EnemySmallDebris] = new Effect::Game::EnemySmallDebrisController();

	crossFilter->SetPower(BloomPower[0], BloomPower[1], BloomPower[2]);
	crossFilter->SetThrethold(BloomThrethold[0], BloomThrethold[1], BloomThrethold[2]);
}

/**************************************
更新処理
***************************************/
void GameParticleManager::Update()
{
	static float power[3] = { BloomPower[0],BloomPower[1], BloomPower[2] };
	static float threth[3] = { BloomThrethold[0],BloomThrethold[1], BloomThrethold[2] };

	Debug::Begin("GameParticle");

	Debug::Slider("power0", power[0], 0.0f, 1.0f);
	Debug::Slider("power1", power[1], 0.0f, 1.0f);
	Debug::Slider("power2", power[2], 0.0f, 1.0f);
	Debug::Slider("threth0", threth[0], 0.0f, 1.0f);
	Debug::Slider("threth1", threth[1], 0.0f, 1.0f);
	Debug::Slider("threth2", threth[2], 0.0f, 1.0f);

	Debug::End();

	SceneParticleManager::Update();
}

/**************************************
エネミーの爆発設定処理
***************************************/
void GameParticleManager::GenerateEnemyExplosion(const D3DXVECTOR3 & position)
{
	controllers[GameEffect::EnemyExplosion]->SetEmitter(position);
	controllers[GameEffect::EnemyDebris]->SetEmitter(position);
}

/**************************************
エネミーの小爆発設定処理
***************************************/
void GameParticleManager::GenerateEnemySmallExplositon(const D3DXVECTOR3 & position)
{
	controllers[GameEffect::EnemyFlame]->SetEmitter(position);
	controllers[GameEffect::EnemySmallDebris]->SetEmitter(position);
}

/**************************************
エネミーの大爆発設定処理
***************************************/
void GameParticleManager::GenerateEnemyBigExplosion(const D3DXVECTOR3 & position)
{
	GenerateEnemyExplosion(position);

	const float OffsetRangeX = 2.0f;
	const float OffsetRangeY = 10.0f;
	const float OffsetRangeZ = 15.0f;

	for (int i = 0; i < 5; i++)
	{
		D3DXVECTOR3 offsetPosition = position;
		offsetPosition.x += Math::RandomRange(-OffsetRangeX, OffsetRangeX);
		offsetPosition.y += Math::RandomRange(-OffsetRangeY, OffsetRangeY);
		offsetPosition.z += Math::RandomRange(-OffsetRangeZ, OffsetRangeZ);

		TaskManager::Instance()->CreateDelayedTask(i* 2.0f, true, [&, offsetPosition]()
		{
			GenerateEnemyExplosion(offsetPosition);
		});
	}
}
