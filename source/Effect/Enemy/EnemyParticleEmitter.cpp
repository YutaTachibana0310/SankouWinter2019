//=====================================
//
//EnemyParticleEmitter.cpp
//�@�\:�G�l�~�[�̃p�[�e�B�N���G�~�b�^
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "EnemyParticleEmitter.h"
#include "../../Controller/EnemyTimeController.h"

/**************************************
�X�V����
***************************************/
void Effect::Enemy::EnemyParticleEmitter::Update()
{
	if (!IsActive())
		return;

	cntFrame += EnemyTimeController::GetTimeScale();

	if (cntFrame >= duration && callback != nullptr)
	{
		callback();
	}
}