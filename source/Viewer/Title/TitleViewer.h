//=====================================
//
//TitleViewer.h
//機能:タイトルビューワ
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _TITLEVIEWER_H_
#define _TITLEVIEWER_H_

#include "../../../main.h"

/**************************************
前方宣言
***************************************/
class Polygon2D;
class TitleGear;

/**************************************
クラス定義
***************************************/
class TitleViewer
{
public:
	TitleViewer();
	~TitleViewer();

	void Update();
	void Draw();

private:
	Polygon2D * titleLogo;

	TitleGear *centerGear;
	TitleGear *rightGear;
	TitleGear *leftGear;
};

#endif