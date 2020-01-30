//=====================================
//
//BaseSmallEnemy.cpp
//�@�\:
//Author:GP12B332 21 ���ԗY��
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
�O���[�o���ϐ�
***************************************/

/**************************************
��������
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
