//=====================================
//
// BaseBigEnemy.cpp
// 機能:
// Author:GP12B332 21 立花雄太
//
//=====================================
#include "BaseBigEnemy.h"
#include "../../../Effect/GameParticleManager.h"

/*************************************
コンストラクタ
***************************************/
BaseBigEnemy::BaseBigEnemy(EnemyHandler* handler) :
	BaseEnemy(handler),
	isDestroied(false)
{

}

/**************************************
爆発処理
***************************************/
void BaseBigEnemy::Explode()
{
	GameParticleManager::Instance()->GenerateEnemyBigExplosion(transform->GetPosition());
}

/**************************************
タイプ判定
***************************************/
BaseEnemy::EnemyType BaseBigEnemy::GetType()
{
	return EnemyType::Big;
}

/**************************************
撃墜判定
***************************************/
bool BaseBigEnemy::IsDestroied()
{
	if (hp > 0.0f)
		return false;

	//NOTE：大型エネミーの撃墜には遅延エフェクトが発生するためフラグで一回のみ撃墜判定を行うようにする
	if (isDestroied)
		return false;

	isDestroied = true;
	return true;
}
