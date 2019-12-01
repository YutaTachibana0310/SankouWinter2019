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

/**************************************
前方宣言
***************************************/
class BaseEnemy;

/**************************************
クラス定義
***************************************/
class EnemyController
{
public:
	EnemyController();
	~EnemyController();

	void Update();
	void Draw();

private:
	BaseEnemy * enemy;
};

#endif