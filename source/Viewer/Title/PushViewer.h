//=====================================
//
//PushViewer.h
//�@�\:�v�b�V���r���[��
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _PUSHVIEWER_H_
#define _PUSHVIEWER_H_

#include "../../../main.h"

#include <functional>

/**************************************
�O���錾
***************************************/
class Polygon2D;

/**************************************
�N���X��`
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