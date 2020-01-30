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
class EnemyEventHandler;
class PlayerController;
class EnemyController;
class EnemyFactory;

/**************************************
クラス定義
***************************************/
class EnemyController
{
public:
	EnemyController(GameCamera *gameCamera);
	~EnemyController();

	void Init();
	void Update();
	void Draw();
	void DrawBullet();

	void CheckEnemyDestroy();

	void SetEnemyEventHandler(EnemyEventHandler *handler);

private:
	std::list<BaseEnemy*> enemyContainer;

	EnemyBulletController *bulletController;

	GameCamera *gameCamera;

	EnemyEventHandler* enemyEventHandler;

	EnemyFactory *factory;

	bool enableGenerateEnemy;
};

#endif