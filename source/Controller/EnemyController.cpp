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
#include "../Camera/GameCamera.h"
#include "../Handler/EnemyHandler.h"

#include "../Actor/Enemy/DemoEnemyActor.h"
#include "../Actor/Enemy/RotateChargeEnemy.h"
#include "../Actor/Enemy/FleetEnemy.h"

#include <type_traits>

/**************************************
グローバル変数
***************************************/
EnemyTween* EnemyTween::mInstance = nullptr;

/**************************************
コンストラクタ
***************************************/
EnemyController::EnemyController(GameCamera *gameCamera) :
	gameCamera(gameCamera)
{
	if (EnemyTween::mInstance == nullptr)
		EnemyTween::mInstance = new EnemyTween();

	ResourceManager::Instance()->LoadMesh("DemoEnemy", "data/MODEL/Enemy/Enemy00.x");
	ResourceManager::Instance()->LoadMesh("RotateEnemy", "data/MODEL/SmallEnemy/SmallEnemy.x");
	ResourceManager::Instance()->LoadMesh("FleetEnemy", "data/MODEL/BigEnemy/BigEnemy.x");

	bulletController = new EnemyBulletController();
	enemyHandler = new EnemyHandler(bulletController);

	BaseEnemy *enemy = nullptr;

	enemy = new RotateChargeEnemy(enemyHandler);
	enemy->SetPosition({ 0.0f, 10.0f, 20.0f });
	enemyContainer.push_back(enemy);
	enemy->Init();

	enemy = new DemoEnemyActor(enemyHandler);
	enemy->SetPosition({ 0.0f, 0.0f, 20.0f });
	enemyContainer.push_back(enemy);
	enemy->Init();

	enemy = new FleetEnemy(enemyHandler);
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

/**************************************
エネミーの撃墜チェック
***************************************/
void EnemyController::CheckEnemyDestroy()
{
	//撃墜判定
	for (auto&& enemy : enemyContainer)
	{
		if (!enemy->IsDestroied())
			continue;

		if(enemy->GetType() == BaseEnemy::Big)
		{
			enemy->Explode();
			gameCamera->Focus(enemy->GetPosition(), [=]()
			{
				enemy->Uninit();
			});
		}
		else
		{
			enemy->Explode();
			enemy->Uninit();
		}
	}

	//非アクティブになったエネミーをリストから削除
	enemyContainer.remove_if([](auto enemy)
	{
		return !enemy->IsActive();
	});
}
