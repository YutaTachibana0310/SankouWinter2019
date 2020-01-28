//=====================================
//
// EventHandler.h
// 機能:エネミーバレット操作ハンドラ
// Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _EVENTHANDLER_H_
#define _EVENTHANDLER_H_

#include "../../main.h"
#include "../Controller/EnemyBulletConfig.h"

/**************************************
前方宣言
***************************************/
class EnemyBulletController;
class PlayerController;
class BackViewer;

/**************************************
クラス定義
***************************************/
class EnemyEventHandler
{
public:
	EnemyEventHandler();

	~EnemyEventHandler();

	void SetBullet(const Transform& shotTransform, EnemyBulletConfig::Type type, float speed);
	void SetWayBullet(const Transform& shotTransform, EnemyBulletConfig::Type type, float speed, int way, float angle);
	void SetCircleBullet(const Transform& shotTransform, EnemyBulletConfig::Type type, float speed, int way);
	void SetStrewBullet(const Transform& shotTransform, EnemyBulletConfig::Type type, float speed, float randomRange);

	void VanishAllBullet();

	void GenerateScoreItem(const D3DXVECTOR3& position);

	void AddScore(int point);

	void SlowdownEnemy();

	void FetchSlowdownState();

	D3DXVECTOR3 GetPlayerPosition() const;

	void GeneratePowerupItem(const D3DXVECTOR3& position);

	void GiveEnemyBulletController(EnemyBulletController *controller);
	void GivePlayerController(PlayerController *controller);
	void GiveBackViewer(BackViewer *viewer);

private:
	EnemyBulletController *bulletController;
	PlayerController *playerController;
	BackViewer *backViewer;

	bool inSlowdown;
};

#endif