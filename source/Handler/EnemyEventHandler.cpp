//=====================================
//
// EventHandler.cpp
// 機能:エネミーバレット操作ハンドラ
// Author:GP12B332 21 立花雄太
//
//=====================================
#include "EnemyEventHandler.h"
#include "../../Framework/Task/TaskManager.h"

#include "../Controller/EnemyBulletController.h"
#include "../Controller/PlayerController.h"
#include "../Controller/EnemyTimeController.h"
#include "../Viewer/Back/BackViewer.h"

/**************************************
グローバル変数
***************************************/

/**************************************
コンストラクタ
***************************************/
EnemyEventHandler::EnemyEventHandler() :
	bulletController(bulletController),
	playerController(playerController)
{
}

/**************************************
デストラクタ
***************************************/
EnemyEventHandler::~EnemyEventHandler()
{
}

/**************************************
バレットセット処理
***************************************/
void EnemyEventHandler::SetBullet(const Transform & shotTransform, EnemyBulletConfig::Type type, float speed)
{
	bulletController->SetBullet(shotTransform, type, speed);
}

/**************************************
WAY弾セット処理
***************************************/
void EnemyEventHandler::SetWayBullet(const Transform & shotTransform, EnemyBulletConfig::Type type, float speed, int way, float angle)
{
	Transform transform = shotTransform;
	transform.Rotate(angle / 2.0f, Vector3::Right);

	float rotAngle = -angle / (way - 1.0f);

	for (int i = 0; i < way; i++)
	{
		bulletController->SetBullet(transform, type, speed);
		transform.Rotate(rotAngle, Vector3::Right);
	}
}

/**************************************
円形弾セット処理
***************************************/
void EnemyEventHandler::SetCircleBullet(const Transform & shotTransform, EnemyBulletConfig::Type type, float speed, int way)
{
	SetWayBullet(shotTransform, type, speed, way, 360.0f);
}

/**************************************
バラマキ弾セット処理
***************************************/
void EnemyEventHandler::SetStrewBullet(const Transform & shotTransform, EnemyBulletConfig::Type type, float speed, float randomRange)
{
	Transform transform = shotTransform;
	transform.Rotate(Math::RandomRange(-randomRange / 2.0f, randomRange / 2.0f), Vector3::Right);	

	bulletController->SetBullet(transform, type, speed);
}

/**************************************
全バレット消失処理
***************************************/
void EnemyEventHandler::VanishAllBullet()
{
}

/**************************************
スコアアイテム生成処理
***************************************/
void EnemyEventHandler::GenerateScoreItem(const D3DXVECTOR3 & position)
{

}

/**************************************
スコア加算処理
***************************************/
void EnemyEventHandler::AddScore(int point)
{

}

/**************************************
エネミー減速処理
***************************************/
void EnemyEventHandler::SlowdownEnemy()
{
	if (!inSlowdown)
		return;

	backViewer->PlayTimeBreak();
	EnemyTimeController::SetTimeScale(0.01f);

	TaskManager::Instance()->CreateDelayedTask(300.0f, false, []()
	{
		EnemyTimeController::SetTimeScale(1.0f);
	});
}

/**************************************
スローダウン判定の保存
***************************************/
void EnemyEventHandler::FetchSlowdownState()
{
	inSlowdown = playerController->InSlowdown();
}

/**************************************
エネミーバレットコントローラ設定処理
***************************************/
void EnemyEventHandler::GiveEnemyBulletController(EnemyBulletController * controller)
{
	bulletController = controller;
}

/**************************************
プレイヤーコントローラ設定処理
***************************************/
void EnemyEventHandler::GivePlayerController(PlayerController * controller)
{
	playerController = controller;
}

/**************************************
バックビューワ設定処理
***************************************/
void EnemyEventHandler::GiveBackViewer(BackViewer * viewer)
{
	backViewer = viewer;
}

