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
	GameParticleManager::Instance()->GenerateScoreEffect(screenPosition, 1000);

	const auto Position = transform->GetPosition();
	GameParticleManager::Instance()->GenerateEnemyExplosion(Position);
	GameScore::Instance()->AddCombo();
	SoundPlayer::Instance()->Play("MiddleExplosion");
}

/**************************************
タイプ判定
***************************************/
BaseEnemy::EnemyType BaseMiddleEnemy::GetType()
{
	return EnemyType::Middle;
}
