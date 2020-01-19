//=====================================
//
//DemoEnemyActor.h
//機能:でもエネミーアクター
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _DEMOENEMYACTOR_H_
#define _DEMOENEMYACTOR_H_

#include "../../../main.h"
#include "../../../Framework/Collider/ColliderObserver.h"
#include "Base/BaseMiddleEnemy.h"

/**************************************
前方宣言
***************************************/
class MeshContainer;
class BoxCollider3D;

/**************************************
クラス定義
***************************************/
class DemoEnemyActor : public BaseMiddleEnemy
{
public:
	DemoEnemyActor(EnemyHandler* handler);
	~DemoEnemyActor();

	void Init();
	void Uninit();
	void Update();
	void Draw();

private:

};

#endif