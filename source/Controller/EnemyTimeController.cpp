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

/**************************************
�^�C���X�P�[���擾
***************************************/
float EnemyTimeController::GetTimeScale()
{
	return timeScale;
}

/**************************************
�^�C���X�P�[���ݒ�
***************************************/
void EnemyTimeController::SetTimeScale(float scale)
{
	timeScale = scale;
}
