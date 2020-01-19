//=====================================
//
// EnemyHandler.cpp
// 機能:エネミーバレット操作ハンドラ
// Author:GP12B332 21 立花雄太
//
//=====================================
#include "EnemyHandler.h"
#include "../Controller/EnemyBulletController.h"

/**************************************
グローバル変数
***************************************/

/**************************************
コンストラクタ
***************************************/
EnemyHandler::EnemyHandler(EnemyBulletController * controller) :
	controller(controller)
{
}

/**************************************
デストラクタ
***************************************/
EnemyHandler::~EnemyHandler()
{
}

/**************************************
バレットセット処理
***************************************/
void EnemyHandler::SetBullet(const Transform & shotTransform, EnemyBulletConfig::Type type, float speed)
{
	controller->SetBullet(shotTransform, type, speed);
}

/**************************************
WAY弾セット処理
***************************************/
void EnemyHandler::SetWayBullet(const Transform & shotTransform, EnemyBulletConfig::Type type, float speed, int way, float angle)
{
	Transform transform = shotTransform;
	transform.Rotate(angle / 2.0f, Vector3::Right);

	float rotAngle = -angle / (way - 1.0f);

	for (int i = 0; i < way; i++)
	{
		controller->SetBullet(transform, type, speed);
		transform.Rotate(rotAngle, Vector3::Right);
	}
}

/**************************************
円形弾セット処理
***************************************/
void EnemyHandler::SetCircleBullet(const Transform & shotTransform, EnemyBulletConfig::Type type, float speed, int way)
{
	SetWayBullet(shotTransform, type, speed, way, 360.0f);
}

/**************************************
バラマキ弾セット処理
***************************************/
void EnemyHandler::SetStrewBullet(const Transform & shotTransform, EnemyBulletConfig::Type type, float speed, float randomRange)
{
	Transform transform = shotTransform;
	transform.Rotate(Math::RandomRange(-randomRange / 2.0f, randomRange / 2.0f), Vector3::Right);	

	controller->SetBullet(transform, type, speed);
}

/**************************************
全バレット消失処理
***************************************/
void EnemyHandler::VanishAllBullet()
{
}

/**************************************
スコアアイテム生成処理
***************************************/
void EnemyHandler::GenerateScoreItem(const D3DXVECTOR3 & position)
{

}

/**************************************
スコア加算処理
***************************************/
void EnemyHandler::AddScore(int point)
{

}

