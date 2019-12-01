//=====================================
//
//GameParticleManager.cpp
//機能:ゲームパーティクルマネージャ
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "GameParticleManager.h"
#include "../../Framework/PostEffect/CrossFilterController.h"

#include "Game\PlayerBulletHit.h"

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

	crossFilter->SetPower(BloomPower[0], BloomPower[1], BloomPower[2]);
	crossFilter->SetThrethold(BloomThrethold[0], BloomThrethold[1], BloomThrethold[2]);
}
