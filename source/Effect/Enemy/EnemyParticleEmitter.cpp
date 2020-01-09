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
	if (!active)
		return;

	cntFrame += EnemyTimeController::GetTimeScale();

	Emit();

	UpdateParticle();

	CheckFinish();
}