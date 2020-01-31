//=====================================
//
// BaseBigEnemy.cpp
// �@�\:
// Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "BaseBigEnemy.h"
#include "../../../Effect/GameParticleManager.h"
#include "../../../Sound/SoundPlayer.h"
#include "../../../../Framework/Camera/Camera.h"

#include "../../../Handler/EnemyEventHandler.h"
#include "../../../System/GameScore.h"

/*************************************
�R���X�g���N�^
***************************************/
BaseBigEnemy::BaseBigEnemy(EnemyEventHandler* handler) :
	BaseEnemy(handler),
	isDestroied(false)
{

}

/**************************************
�I������
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
��������
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
�^�C�v����
***************************************/
BaseEnemy::EnemyType BaseBigEnemy::GetType()
{
	return EnemyType::Big;
}

/**************************************
���Ĕ���
***************************************/
bool BaseBigEnemy::IsDestroied()
{
	if (hp > 0.0f)
		return false;

	//NOTE�F��^�G�l�~�[�̌��Ăɂ͒x���G�t�F�N�g���������邽�߃t���O�ň��̂݌��Ĕ�����s���悤�ɂ���
	if (isDestroied)
		return false;

	isDestroied = true;
	return true;
}
