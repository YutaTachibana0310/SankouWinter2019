//=====================================
//
//PowerupItemActor.h
//機能:パワーアップアイテムアクター
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _POWEUPITEMACTOR_H_
#define _POWEUPITEMACTOR_H_

#include "../../../main.h"
#include "../../../Framework/Renderer3D/BillboardObject.h"

/**************************************
前方宣言
***************************************/
class BoxCollider3D;
class BoardPolygon;

/**************************************
クラス定義
***************************************/
class PowerupItemActor : public BillboardObject
{
public:
	PowerupItemActor();
	~PowerupItemActor();

	void Init();
	void Uninit();
	void Update();
	void Draw();

	static const D3DXVECTOR3 MoveBorder;

private:
	BoardPolygon * polygon;

	D3DXVECTOR3 moveDir;
	float cntFrame;
};

#endif