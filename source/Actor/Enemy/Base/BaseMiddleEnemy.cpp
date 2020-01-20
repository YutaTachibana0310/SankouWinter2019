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

/**************************************
グローバル変数
***************************************/

/**************************************
爆発処理
***************************************/
void BaseMiddleEnemy::Explode()
{
	GameParticleManager::Instance()->GenerateEnemyExplosion(transform->GetPosition());
	SoundPlayer::Instance()->Play("MiddleExplosion");
}

/**************************************
タイプ判定
***************************************/
BaseEnemy::EnemyType BaseMiddleEnemy::GetType()
{
	return EnemyType::Middle;
}
