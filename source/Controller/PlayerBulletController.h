//=====================================
//
//PlayerBulletController.h
//機能:プレイヤーバレットコントローラ
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _PLAYERBULLETCONTROLLER_H_
#define _PLAYERBULLETCONTROLLER_H_

#include "../../main.h"
#include <vector>

/**************************************
前方宣言
***************************************/
class PlayerBulletActor;

/**************************************
クラス定義
***************************************/
class PlayerBulletController
{
public:
	PlayerBulletController();
	~PlayerBulletController();

	void Update();
	void Draw();

	void FireBullet(const D3DXVECTOR3& pos);

private:
	std::vector<PlayerBulletActor*> bulletContainer;
};
#endif