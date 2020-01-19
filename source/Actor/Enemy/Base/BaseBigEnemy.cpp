//=====================================
//
// BaseBigEnemy.cpp
// �@�\:
// Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "BaseBigEnemy.h"
#include "../../../Effect/GameParticleManager.h"

/*************************************
�R���X�g���N�^
***************************************/
BaseBigEnemy::BaseBigEnemy(EnemyHandler* handler) :
	BaseEnemy(handler),
	isDestroied(false)
{

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
