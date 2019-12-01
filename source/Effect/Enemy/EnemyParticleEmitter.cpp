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
����������
***************************************/
void Effect::Enemy::EnemyParticleEmitter::Init(std::function<void()>& callback)
{
	prevEmit = 0.0f;
	BaseEmitter::Init(callback);
}

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

/**************************************
���o����
***************************************/
bool Effect::Enemy::EnemyParticleEmitter::Emit(std::vector<BaseParticle*>& container)
{
	if (cntFrame < prevEmit)
		return true;

	prevEmit = floorf(cntFrame);
	return BaseEmitter::Emit(container);
}
