//=====================================
//
// PlayerColliderVIewer.h
// 機能:プレイヤーの当たり判定ビューワ
// Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _PLAYERCOLLIDERVIEWER_H_
#define _PLAYERCOLLIDERVIEWER_H_

#include "../../../main.h"
#include "../../../Framework/Renderer3D/BillboardObject.h"

/**************************************
前方宣言
***************************************/
class BoardPolygon;

/**************************************
クラス定義
***************************************/
class PlayerColliderViewer : public BillboardObject
{
public:
	PlayerColliderViewer();
	~PlayerColliderViewer();

	void Update();
	void Draw();

	static const int PeriodAnimation;
	static const int MaxAnimation;

private:
	BoardPolygon *polygon;

	int cntFrame;
	int animIndex;
};

#endif