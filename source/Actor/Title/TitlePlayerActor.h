//=====================================
//
//TitlePlayerActor.h
//機能:プレイヤーアクター
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _PLAYERACTOR_H_
#define _PLAYERACTOR_H_

#include "../../../main.h"

#include <vector>
#include <functional>

/**************************************
前方宣言
***************************************/
class MeshContainer;
class PlayerTurretActor;
class PlayerTurretRoot;
class BaseEmitter;

/**************************************
クラス定義
***************************************/
class TitlePlayerActor : public GameObject
{
public:
	TitlePlayerActor();
	virtual ~TitlePlayerActor();

	virtual void Init();
	virtual void Uninit();
	virtual void Update();
	virtual void Draw();

private:
	MeshContainer * mesh;
	BaseEmitter *trailEmitter;

	float cntShotFrame;

	bool enableShot;
	bool enableMove;

	int currentLevel;
};

#endif