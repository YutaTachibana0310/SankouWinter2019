//=====================================
//
//EnemyController.cpp
//機能:エネミーコントローラ
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "EnemyController.h"
#include "../../Framework/Tool/DebugWindow.h"

#include "EnemyTimeController.h"
#include "EnemyBulletController.h"
#include "../System/EnemyTween.h"
#include "../Actor/Enemy/DemoEnemyActor.h"

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

	bulletController = new EnemyBulletController();

	enemy = new DemoEnemyActor();
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

	SAFE_DELETE(enemy);
}

/**************************************
更新処理
***************************************/
void EnemyController::Update()
{
	enemy->Update();
	EnemyTween::mInstance->Update();

	bulletController->Update();
}

/**************************************
描画処理
***************************************/
void EnemyController::Draw()
{
	enemy->Draw();
}

/**************************************
バレット描画処理
***************************************/
void EnemyController::DrawBullet()
{
	bulletController->Draw();
}