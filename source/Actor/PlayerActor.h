//=====================================
//
//PlayerActor.h
//機能:プレイヤーアクター
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _PLAYERACTOR_H_
#define _PLAYERACTOR_H_

#include "../../main.h"

/**************************************
前方宣言
***************************************/
class MeshContainer;

/**************************************
クラス定義
***************************************/
class PlayerActor : public GameObject
{
public:
	PlayerActor();
	virtual ~PlayerActor();

	virtual void Init();
	virtual void Uninit();
	virtual void Update();
	virtual void Draw();

	static const float SpeedMove;
	static const D3DXVECTOR3 BorderMove;

private:
	MeshContainer * mesh;

	void Move(const D3DXVECTOR3& dir);
};

#endif