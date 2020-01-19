//=====================================
//
//BaseSmallEnemy.cpp
//機能:
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "BaseSmallEnemy.h"
#include "../../../Effect/GameParticleManager.h"

/**************************************
グローバル変数
***************************************/

/**************************************
爆発処理
***************************************/
void BaseSmallEnemy::Explode()
{
	GameParticleManager::Instance()->GenerateEnemySmallExplositon(transform->GetPosition());
}

/**************************************
タイプ判定
***************************************/
BaseEnemy::EnemyType BaseSmallEnemy::GetType()
{
	return EnemyType::Small;
}
