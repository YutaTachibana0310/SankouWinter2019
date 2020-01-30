//=====================================
//
// BaseMiddleEnemy.cpp
// 機能:
// Author:GP12B332 21 立花雄太
//
//=====================================
#include "BaseMiddleEnemy.h"
#include "../../../Effect/GameParticleManager.h"
#include "../../../Sound/SoundPlayer.h"
#include "../../../../Framework/Camera/Camera.h"
#include "../../../System/GameScore.h"

/**************************************
グローバル変数
***************************************/

/**************************************
爆発処理
***************************************/
void BaseMiddleEnemy::Explode()
{
	const auto screenPosition = Camera::MainCamera()->Projection(transform->GetPosition());
	GameParticleManager::Instance()->GenerateEnergyEffect(screenPosition, 5.0f);

	GameParticleManager::Instance()->GenerateEnemyExplosion(transform->GetPosition());
	SoundPlayer::Instance()->Play("MiddleExplosion");
	GameScore::Instance()->AddScore(1000);
	GameScore::Instance()->AddCombo();
}

/**************************************
タイプ判定
***************************************/
BaseEnemy::EnemyType BaseMiddleEnemy::GetType()
{
	return EnemyType::Middle;
}
