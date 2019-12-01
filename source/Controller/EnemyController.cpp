//=====================================
//
//EnemyController.cpp
//�@�\:�G�l�~�[�R���g���[��
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "EnemyController.h"
#include "../../Framework/Tool/DebugWindow.h"

#include "EnemyTimeController.h"
#include "../System/EnemyTween.h"
#include "../Actor/Enemy/DemoEnemyActor.h"

/**************************************
�O���[�o���ϐ�
***************************************/
EnemyTween* EnemyTween::mInstance = nullptr;

/**************************************
�R���X�g���N�^
***************************************/
EnemyController::EnemyController()
{
	if (EnemyTween::mInstance == nullptr)
		EnemyTween::mInstance = new EnemyTween();

	enemy = new DemoEnemyActor();
	enemy->Init();
}

/**************************************
�f�X�g���N�^
***************************************/
EnemyController::~EnemyController()
{
	EnemyTween::mInstance->ClearAll();
	SAFE_DELETE(EnemyTween::mInstance);

	SAFE_DELETE(enemy);
}

/**************************************
�X�V����
***************************************/
void EnemyController::Update()
{
	Debug::Begin("Enemy");
	static float timeScale = 1.0f;
	EnemyTimeController::SetTimeScale(timeScale);
	Debug::Slider("timeScale", timeScale, 0.001f, 1.0f);

	Debug::End();

	enemy->Update();
	EnemyTween::mInstance->Update();
}

/**************************************
�`�揈��
***************************************/
void EnemyController::Draw()
{
	enemy->Draw();
}
