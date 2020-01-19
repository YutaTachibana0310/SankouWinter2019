//=====================================
//
// BaseBigEnemy.cpp
// 機能:
// Author:GP12B332 21 立花雄太
//
//=====================================
#include "BaseBigEnemy.h"
#include "../../../Effect/GameParticleManager.h"

/**************************************
グローバル変数
***************************************/

/**************************************
爆発処理
***************************************/
void BaseBigEnemy::Explode()
{
	GameParticleManager::Instance()->GenerateEnemyBigExplosion(transform->GetPosition());
}
