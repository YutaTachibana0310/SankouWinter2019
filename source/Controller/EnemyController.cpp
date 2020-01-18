//=====================================
//
//EnemyController.cpp
//機能:エネミーコントローラ
//Author:GP12B332 21 立花雄太
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
グローバル変数
***************************************/
EnemyTween* EnemyTween::mInstance = nullptr;

/**************************************
コンストラクタ
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
デストラクタ
***************************************/
EnemyController::~EnemyController()
{
	EnemyTween::mInstance->ClearAll();
	SAFE_DELETE(EnemyTween::mInstance);

	SAFE_DELETE(bulletController);

	Utility::DeleteContainer(enemyContainer);
}

/**************************************
更新処理
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
描画処理
***************************************/
void EnemyController::Draw()
{
	for (auto&& enemy : enemyContainer)
	{
		enemy->Draw();
	}
}

/**************************************
バレット描画処理
***************************************/
void EnemyController::DrawBullet()
{
	bulletController->Draw();
}