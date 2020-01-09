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

#include "Game\PlayerBulletHit.h"
#include "Enemy\EnemyExplosion.h"
#include "Enemy/EnemyDebris.h"

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
void GameParticleManager::GenerateEnemyExplostion(const D3DXVECTOR3 & position)
{
	controllers[GameEffect::EnemyExplosion]->SetEmitter(position);
	controllers[GameEffect::EnemyDebris]->SetEmitter(position);
}
