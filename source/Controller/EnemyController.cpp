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

	SAFE_DELETE(enemy);
}

/**************************************
更新処理
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
描画処理
***************************************/
void EnemyController::Draw()
{
	enemy->Draw();
}
