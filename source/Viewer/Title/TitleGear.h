//=====================================
//
//TitleGear.h
//機能:タイトル歯車
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _TITLEGEAR_H_
#define _TITLEGEAR_H_

#include "../../../main.h"

/**************************************
前方宣言
***************************************/
class Polygon2D;

/**************************************
クラス定義
***************************************/
class TitleGear : public GameObject
{
public:
	TitleGear();
	~TitleGear();

	void Update();
	void Draw();

private:
	Polygon2D * innerGear;
	Polygon2D * outerGear;
};
#endif