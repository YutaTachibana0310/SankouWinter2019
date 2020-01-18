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
#include "../Actor/Enemy/FleetEnemy.h"

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
	ResourceManager::Instance()->LoadMesh("FleetEnemy", "data/MODEL/BigEnemy/BigEnemy.x");

	bulletController = new EnemyBulletController();

	BaseEnemy *enemy = nullptr;

	enemy = new RotateChargeEnemy();
	enemy->SetPosition({ 0.0f, 10.0f, 20.0f });
	enemyContainer.push_back(enemy);
	enemy->Init();

	enemy = new DemoEnemyActor();
	enemy->SetPosition({ 0.0f, 0.0f, 20.0f });
	enemyContainer.push_back(enemy);
	enemy->Init();

	enemy = new FleetEnemy();
	enemy->SetPosition({ 0.0f, -10.0f, 20.0f });
	enemyContainer.push_back(enemy);
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

	Utility::DeleteContainer(enemyContainer);
}

/**************************************
�X�V����
***************************************/
void EnemyController::Update()
{
	for (auto&& enemy : enemyContainer)
	{
		enemy->Update();
	}

	EnemyTween::mInstance->Update();

	bulletController->Update();
}

/**************************************
�`�揈��
***************************************/
void EnemyController::Draw()
{
	for (auto&& enemy : enemyContainer)
	{
		enemy->Draw();
	}
}

/**************************************
�o���b�g�`�揈��
***************************************/
void EnemyController::DrawBullet()
{
	bulletController->Draw();
}