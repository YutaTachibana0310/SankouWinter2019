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

#include "../../../Handler/EnemyEventHandler.h"

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
	SoundPlayer::Instance()->Play("BigExplosion");
	handle->VanishAllBullet();
	handle->SlowdownEnemy();
}

/**************************************
��������
***************************************/
void BaseBigEnemy::Explode()
{
	GameParticleManager::Instance()->GenerateEnemyBigExplosion(transform->GetPosition());
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
