//=====================================
//
//ResultViewer.h
//機能:リザルトビューワ
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _RESULTVIEWER_H_
#define _RESULTVIEWER_H_

#include "../../../main.h"

/**************************************
前方宣言
***************************************/
class Polygon2D;

/**************************************
クラス定義
***************************************/
class ResultViewer
{
public:
	ResultViewer();
	~ResultViewer();

	void Update();
	void Draw();

private:
	Polygon2D * bg;

};
#endif