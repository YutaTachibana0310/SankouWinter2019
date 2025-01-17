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
#include "../../Library/json11/json11.hpp"

#include "EnemyTimeController.h"
#include "EnemyBulletController.h"
#include "../System/EnemyTween.h"
#include "../Camera/GameCamera.h"
#include "../Handler/EnemyEventHandler.h"
#include "EnemyFactory.h"

#include "../Actor/Enemy/DemoEnemyActor.h"
#include "../Actor/Enemy/RotateChargeEnemy.h"
#include "../Actor/Enemy/FleetEnemy.h"
#include "../Actor/Enemy/SnipeEnemyActor.h"
#include "../Actor/Enemy/MiddleWayEnemy.h"
#include "../Actor/Enemy/TutorialEnemy.h"

#include <type_traits>
#include <fstream>

/**************************************
グローバル変数
***************************************/
EnemyTween* EnemyTween::mInstance = nullptr;

/**************************************
コンストラクタ
***************************************/
EnemyController::EnemyController(GameCamera* gameCamera) :
	gameCamera(gameCamera),
	enableGenerateEnemy(false)
{
	if (EnemyTween::mInstance == nullptr)
		EnemyTween::mInstance = new EnemyTween();

	ResourceManager::Instance()->LoadMesh("DemoEnemy", "data/MODEL/Enemy/Enemy00.x");
	ResourceManager::Instance()->LoadMesh("RotateEnemy", "data/MODEL/SmallEnemy/SmallEnemy.x");
	ResourceManager::Instance()->LoadMesh("FleetEnemy", "data/MODEL/BigEnemy/BigEnemy.x");

	bulletController = new EnemyBulletController();
	factory = new EnemyFactory(&enemyEventHandler);

	factory->Load("data/DATA/EnemyData.json");
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
エネミー初期化処理
***************************************/
void EnemyController::Init()
{
	enableGenerateEnemy = true;
}

/**************************************
更新処理
***************************************/
void EnemyController::Update()
{
	//エネミーの生成
	if (enableGenerateEnemy)
	{
		std::list<BaseEnemy*> newEnemy = factory->Create();
		if (!newEnemy.empty())
		{
			enemyContainer.splice(enemyContainer.end(), newEnemy);
		}
	}

	//更新
	for (auto&& enemy : enemyContainer)
	{
		enemy->Update();
	}

	//トゥイーン更新
	EnemyTween::mInstance->Update();

	//バレット更新
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
			enemyEventHandler->FetchSlowdownState();
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

/**************************************
ハンドラー作成
***************************************/
void EnemyController::SetEnemyEventHandler(EnemyEventHandler *handler)
{
	enemyEventHandler = handler;
	enemyEventHandler->GiveEnemyBulletController(bulletController);

	BaseEnemy *enemy = nullptr;

	//enemy = new RotateChargeEnemy(enemyEventHandler);
	//enemy->SetPosition({ 0.0f, 10.0f, 60.0f });
	//enemyContainer.push_back(enemy);
	//enemy->Init();

	//enemy = new DemoEnemyActor(enemyEventHandler);
	//enemy->SetPosition({ 0.0f, 0.0f, 50.0f });
	//enemyContainer.push_back(enemy);
	//enemy->Init();

	//enemy = new FleetEnemy(enemyEventHandler);
	//enemy->SetPosition({ 0.0f, -50.0f, 20.0f });
	//enemyContainer.push_back(enemy);
	//enemy->Init();

	//enemy = new SnipeEnemyActor(enemyEventHandler);
	//enemy->SetPosition({ 0.0f, 20.0f, 60.0f });
	//enemyContainer.push_back(enemy);
	//enemy->Init();

	//enemy = new MiddleWayEnemy(enemyEventHandler);
	//enemy->SetPosition({ 0.0f, -50.0f, 30.0f });
	//enemy->Init();
	//enemyContainer.push_back(enemy);
}

/**************************************
チュートリアル用エネミー作成
***************************************/
void EnemyController::CreateTutorialEnemy()
{
	TutorialEnemyActor *actor = new TutorialEnemyActor(enemyEventHandler);
	actor->Init();
	enemyContainer.push_back(actor);
}

/**************************************
クリア判定
***************************************/
bool EnemyController::IsClear()
{
	return enemyContainer.empty() && factory->IsFinished();
}
