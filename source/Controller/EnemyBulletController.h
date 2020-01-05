//=====================================
//
// EnemyBulletController.h
// 機能:エネミーバレットコントローラ
// Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _ENEMYBULLETCONTROLLER_H_
#define _ENEMYBULLETCONTROLLER_H_

#include "../../main.h"
#include "EnemyBulletConfig.h"

#include <vector>

/**************************************
前方宣言
***************************************/
class EnemyBulletActor;

/**************************************
クラス定義
***************************************/
class EnemyBulletController
{
public:
	EnemyBulletController();
	~EnemyBulletController();

	void Update();
	void Draw();
	
	void SetBullet(const Transform& shotTransform, EnemyBulletConfig::Type type);

	static const unsigned MaxBullet;

private:
	std::vector<EnemyBulletActor*> bulletContainer;
	unsigned cntBullet;
};

#endif