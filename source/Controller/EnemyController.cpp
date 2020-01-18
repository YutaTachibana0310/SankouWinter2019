//=====================================
//
//EnemyController.cpp
//�@�\:�G�l�~�[�R���g���[��
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "EnemyController.h"
#include "../../Framework/Tool/DebugWindow.h"
#include "../../Framework/Resource/ResourceManager.h"

#include "EnemyTimeController.h"
#include "EnemyBulletController.h"
#include "../System/EnemyTween.h"

#include "../Actor/Enemy/DemoEnemyActor.h"
#include "../Actor/Enemy/RotateChargeEnemy.h"

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

	ResourceManager::Instance()->LoadMesh("DemoEnemy", "data/MODEL/Enemy/Enemy00.x");
	ResourceManager::Instance()->LoadMesh("RotateEnemy", "data/MODEL/SmallEnemy/SmallEnemy.x");

	bulletController = new EnemyBulletController();

	enemy = new RotateChargeEnemy();
	enemy->Init();
}

/**************************************
�f�X�g���N�^
***************************************/
EnemyController::~EnemyController()
{
	EnemyTween::mInstance->ClearAll();
	SAFE_DELETE(EnemyTween::mInstance);

	SAFE_DELETE(bulletController);

	SAFE_DELETE(enemy);
}

/**************************************
�X�V����
***************************************/
void EnemyController::Update()
{
	enemy->Update();
	EnemyTween::mInstance->Update();

	bulletController->Update();
}

/**************************************
�`�揈��
***************************************/
void EnemyController::Draw()
{
	enemy->Draw();
}

/**************************************
�o���b�g�`�揈��
***************************************/
void EnemyController::DrawBullet()
{
	bulletController->Draw();
}