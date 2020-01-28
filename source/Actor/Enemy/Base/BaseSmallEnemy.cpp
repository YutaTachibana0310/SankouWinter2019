//=====================================
//
//BaseSmallEnemy.cpp
//�@�\:
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "BaseSmallEnemy.h"
#include "../../../Effect/GameParticleManager.h"
#include "../../../Sound/SoundPlayer.h"
#include "../../../Handler/EnemyEventHandler.h"

/**************************************
�O���[�o���ϐ�
***************************************/

/**************************************
��������
***************************************/
void BaseSmallEnemy::Explode()
{
	GameParticleManager::Instance()->GenerateEnemySmallExplositon(transform->GetPosition());
	SoundPlayer::Instance()->Play("SmallExplosion");

	if (generateItem)
		handle->GeneratePowerupItem(transform->GetPosition());
}

/**************************************
�^�C�v����
***************************************/
BaseEnemy::EnemyType BaseSmallEnemy::GetType()
{
	return EnemyType::Small;
}

/**************************************
�A�C�e���𔭐������邩
***************************************/
void BaseSmallEnemy::SetPowerupItem(bool state)
{
	generateItem = state;
}
