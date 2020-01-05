//=====================================
//
// EnemyBulletHandler.h
// 機能:エネミーバレット操作ハンドラ
// Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _ENEMYBULLETHANDLER_H_
#define _ENEMYBULLETHANDLER_H_

#include "../../main.h"
#include "../Controller/EnemyBulletConfig.h"

/**************************************
前方宣言
***************************************/
class EnemyBulletController;

/**************************************
クラス定義
***************************************/
class EnemyBulletHandler
{
public:
	EnemyBulletHandler(EnemyBulletController* controller);
	~EnemyBulletHandler();

	void SetBullet(const Transform& shotTransform, EnemyBulletConfig::Type type, float speed);
	void SetWayBullet(const Transform& shotTransform, EnemyBulletConfig::Type type, float speed, int way, float angle);
	void SetCircleBullet(const Transform& shotTransform, EnemyBulletConfig::Type type, float speed, int way);
	void SetStrewBullet(const Transform& shotTransform, EnemyBulletConfig::Type type, float speed, float randomRange);

	void VanishAllBullet();

private:
	EnemyBulletController *controller;
};

#endif