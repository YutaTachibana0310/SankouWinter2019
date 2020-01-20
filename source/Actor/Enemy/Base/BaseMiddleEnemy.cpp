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

/**************************************
�O���[�o���ϐ�
***************************************/

/**************************************
��������
***************************************/
void BaseMiddleEnemy::Explode()
{
	GameParticleManager::Instance()->GenerateEnemyExplosion(transform->GetPosition());
	SoundPlayer::Instance()->Play("MiddleExplosion");
}

/**************************************
�^�C�v����
***************************************/
BaseEnemy::EnemyType BaseMiddleEnemy::GetType()
{
	return EnemyType::Middle;
}
