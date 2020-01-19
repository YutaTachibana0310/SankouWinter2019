//=====================================
//
//EnemyController.h
//機能:エネミーコントローラ
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _ENEMYCONTROLLER_H_
#define _ENEMYCONTROLLER_H_

#include "../../main.h"
#include <list>

/**************************************
前方宣言
***************************************/
class BaseEnemy;
class EnemyBulletController;
class GameCamera;
class EnemyHandler;

/**************************************
クラス定義
***************************************/
class EnemyController
{
public:
	EnemyController(GameCamera *gameCamera);
	~EnemyController();

	void Update();
	void Draw();
	void DrawBullet();

	void CheckEnemyDestroy();

private:
	std::list<BaseEnemy*> enemyContainer;

	EnemyBulletController *bulletController;

	EnemyHandler* enemyHandler;

	GameCamera *gameCamera;
};

#endif