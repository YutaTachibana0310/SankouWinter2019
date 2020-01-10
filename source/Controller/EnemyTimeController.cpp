//=====================================
//
//EnemyTimeController.cpp
//�@�\:
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "EnemyTimeController.h"

/**************************************
static�����o
***************************************/
float EnemyTimeController::timeScale = 1.0f;
bool EnemyTimeController::isSlowDownBullet = false;

/**************************************
�^�C���X�P�[���擾
***************************************/
float EnemyTimeController::GetTimeScale()
{
	return timeScale * FixedTime::GetTimeScale();
}

/**************************************
�^�C���X�P�[���ݒ�
***************************************/
void EnemyTimeController::SetTimeScale(float scale)
{
	timeScale = scale;
}

/**************************************
�o���b�g�̃^�C���X�P�[���擾
***************************************/
float EnemyTimeController::GetBulletTimeScale()
{
	float bulletTimeScale = isSlowDownBullet ? 0.1f : 1.0f;
	return bulletTimeScale * timeScale * FixedTime::GetTimeScale();
}

/**************************************
�o���b�g�̃^�C���X�P�[���ݒ菈��
***************************************/
void EnemyTimeController::SlowDownBullet(bool enable)
{
	isSlowDownBullet = enable;
}

