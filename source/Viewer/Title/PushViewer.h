//=====================================
//
//PushViewer.h
//機能:プッシュビューワ
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _PUSHVIEWER_H_
#define _PUSHVIEWER_H_

#include "../../../main.h"

#include <functional>

/**************************************
前方宣言
***************************************/
class Polygon2D;

/**************************************
クラス定義
***************************************/
class PushViewer : public GameObject
{
public:
	PushViewer();
	~PushViewer();

	void Draw();

private:
	std::shared_ptr<Polygon2D> polygon;

	std::function<void()> onFinishFadeIn;
	std::function<void()> onFinishFadeOut;

	void OnFinishFadeIn();
	void OnFinishFadeOut();
};
#endif