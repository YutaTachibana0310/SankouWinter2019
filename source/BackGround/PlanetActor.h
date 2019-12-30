//=====================================
//
// PlanetActor.h
// 機能:惑星アクター
// Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _PLANETACTOR_H_
#define _PLANETACTOR_H_

#include "../../main.h"

/**************************************
前方宣言
***************************************/
class MeshContainer;

/**************************************
クラス定義
***************************************/
class PlanetActor : public GameObject
{
public:
	PlanetActor();
	virtual ~PlanetActor();

	void Update();
	void Draw();

	static const D3DXVECTOR3 InitPos;

private:
	MeshContainer *mesh;
};

#endif