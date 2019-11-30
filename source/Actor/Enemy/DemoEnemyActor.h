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

/**************************************
前方宣言
***************************************/
class MeshContainer;

/**************************************
クラス定義
***************************************/
class DemoEnemyActor : public GameObject
{
public:
	DemoEnemyActor();
	~DemoEnemyActor();

	void Init();
	void Uninit();
	void Update();
	void Draw();

private:
	MeshContainer * mesh;
};

#endif