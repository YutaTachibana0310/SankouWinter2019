//=====================================
//
//BaseSmallEnemy.cpp
//�@�\:
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "BaseSmallEnemy.h"
#include "../../../Effect/GameParticleManager.h"

/**************************************
�O���[�o���ϐ�
***************************************/

/**************************************
��������
***************************************/
void BaseSmallEnemy::Explode()
{
	GameParticleManager::Instance()->GenerateEnemySmallExplositon(transform->GetPosition());
}

/**************************************
�^�C�v����
***************************************/
BaseEnemy::EnemyType BaseSmallEnemy::GetType()
{
	return EnemyType::Small;
}
