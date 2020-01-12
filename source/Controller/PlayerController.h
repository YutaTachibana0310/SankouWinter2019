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

private:
	PlayerActor * player;
	PlayerBulletController *bulletController;

	float cntEnergy;

	static const float MaxEnergy;

	void InputEnemyBulletSlowDown();
};
#endif