//=====================================
//
//BaseSmallEnemy.cpp
//機能:
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "BaseSmallEnemy.h"
#include "../../../../Framework/Camera/Camera.h"
#include "../../../Effect/GameParticleManager.h"
#include "../../../Sound/SoundPlayer.h"
#include "../../../Handler/EnemyEventHandler.h"
#include "../../../Effect/GameParticleManager.h"
#include "../../../System/GameScore.h"

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

	const D3DXVECTOR3 screenPos = Camera::MainCamera()->Projection(transform->GetPosition());
	GameParticleManager::Instance()->GenerateEnergyEffect(screenPos, 0.1f);

	if (generateItem)
		handle->GeneratePowerupItem(transform->GetPosition());

	GameScore::Instance()->AddScore(50);
}

/**************************************
タイプ判定
***************************************/
BaseEnemy::EnemyType BaseSmallEnemy::GetType()
{
	return EnemyType::Small;
}

/**************************************
アイテムを発生させるか
***************************************/
void BaseSmallEnemy::SetPowerupItem(bool state)
{
	generateItem = state;
}
