//=====================================
//
// BaseMiddleEnemy.cpp
// �@�\:
// Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "BaseMiddleEnemy.h"
#include "../../../Effect/GameParticleManager.h"

/**************************************
�O���[�o���ϐ�
***************************************/

/**************************************
��������
***************************************/
void BaseMiddleEnemy::Explode()
{
	GameParticleManager::Instance()->GenerateEnemyExplosion(transform->GetPosition());
}
