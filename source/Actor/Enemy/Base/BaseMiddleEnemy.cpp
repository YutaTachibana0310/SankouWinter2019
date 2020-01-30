//=====================================
//
// BaseMiddleEnemy.cpp
// �@�\:
// Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "BaseMiddleEnemy.h"
#include "../../../Effect/GameParticleManager.h"
#include "../../../Sound/SoundPlayer.h"
#include "../../../../Framework/Camera/Camera.h"
#include "../../../System/GameScore.h"

/**************************************
�O���[�o���ϐ�
***************************************/

/**************************************
��������
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
�^�C�v����
***************************************/
BaseEnemy::EnemyType BaseMiddleEnemy::GetType()
{
	return EnemyType::Middle;
}
