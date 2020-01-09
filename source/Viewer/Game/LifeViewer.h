//=====================================
//
// LifeViewer.h
// 機能:残機ビューワ
// Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _LIFEVIEWER_H_
#define _LIFEVIEWER_H_

#include "../../../main.h"
#include "../../../Framework/Renderer2D/TextViewer.h"

#include <vector>

/**************************************
前方宣言
***************************************/
class Polygon2D;

/**************************************
クラス定義
***************************************/
class LifeViewer : public TextViewer
{
public:
	LifeViewer();
	~LifeViewer();

	void Update();
	void Draw();

	void SetCount(int num);

private:
	int count;
	std::vector<Polygon2D*> container;
};

#endif