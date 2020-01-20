//=====================================
//
//BaseSmallEnemy.cpp
//機能:
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "BaseSmallEnemy.h"
#include "../../../Effect/GameParticleManager.h"
#include "../../../Sound/SoundPlayer.h"

/**************************************
グローバル変数
***************************************/

/**************************************
爆発処理
***************************************/
void BaseSmallEnemy::Explode()
{
	GameParticleManager::Instance()->GenerateEnemySmallExplositon(transform->GetPosition());
	SoundPlayer::Instance()->Play("SmallExplosion");
}

/**************************************
タイプ判定
***************************************/
BaseEnemy::EnemyType BaseSmallEnemy::GetType()
{
	return EnemyType::Small;
}
