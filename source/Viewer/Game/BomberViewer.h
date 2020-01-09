//=====================================
//
// BomberViewer.h
// 機能:ボンバービューワ
// Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _BOMBERVIEWER_H_
#define _BOMBERVIEWER_H_

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
class BomberViewer : public TextViewer
{
public:
	BomberViewer();
	~BomberViewer();

	void Update();
	void Draw();

	void SetCount(int num);

private:
	std::vector<Polygon2D*> container;
	int count;
};

#endif