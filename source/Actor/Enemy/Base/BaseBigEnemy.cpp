//=====================================
//
// BaseBigEnemy.cpp
// 機能:
// Author:GP12B332 21 立花雄太
//
//=====================================
#include "BaseBigEnemy.h"
#include "../../../Effect/GameParticleManager.h"
#include "../../../Sound/SoundPlayer.h"
#include "../../../../Framework/Camera/Camera.h"

#include "../../../Handler/EnemyEventHandler.h"
#include "../../../System/GameScore.h"

/*************************************
コンストラクタ
***************************************/
BaseBigEnemy::BaseBigEnemy(EnemyEventHandler* handler) :
	BaseEnemy(handler),
	isDestroied(false)
{

}

/**************************************
終了処理
***************************************/
void BaseBigEnemy::Uninit()
{
	if (hp <= 0.0f)
	{
		SoundPlayer::Instance()->Play("BigExplosion");
		handle->VanishAllBullet();
		handle->SlowdownEnemy();
	}
}

/**************************************
爆発処理
***************************************/
void BaseBigEnemy::Explode()
{
	const auto ScreenPosition = Camera::MainCamera()->Projection(transform->GetPosition());
	GameParticleManager::Instance()->GenerateEnergyEffect(ScreenPosition, 30.0f);
	GameParticleManager::Instance()->GenerateEnergyEffect(ScreenPosition, 5000);

	GameParticleManager::Instance()->GenerateEnemyBigExplosion(transform->GetPosition());

	GameScore::Instance()->AddCombo();
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
