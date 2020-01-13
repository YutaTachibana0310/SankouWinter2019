//=====================================
//
//PlayerController.h
//機能:プレイヤーコントローラ
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _PLAYERCONTROLLER_H_
#define _PLAYERCONTROLLER_H_

#include "../../main.h"

/**************************************
前方宣言
***************************************/
class PlayerActor;
class PlayerBulletController;
class ColliderObserver;

/**************************************
クラス定義
***************************************/
class PlayerController
{
public:
	PlayerController();
	~PlayerController();

	void Update();
	void Draw();
	void DrawBullet();

	float GetPercentEnergy() const;
	int GetCntLife() const;
	int GetCntBomb() const;

private:
	PlayerActor * player;
	PlayerBulletController *bulletController;

	float cntEnergy;
	int cntBomb;
	int cntLife;

	static const float MaxEnergy;
	static const int MaxLife;
	static const int MaxBomb;

	void InputEnemyBulletSlowDown();
	void CollisionPlayer(ColliderObserver* other);
};
#endif