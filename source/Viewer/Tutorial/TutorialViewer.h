//=====================================
//
//TutorialViewer.h
//�@�\:�`���[�g���A���r���[��
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _TUTORIALVIEWER_H_
#define _TUTORIALVIEWER_H_

#include "../../../main.h"
#include <functional>

/**************************************
�O���錾
***************************************/
class Polygon2D;
class TextViewer;

/**************************************
�N���X��`
***************************************/
class TutorialViewer
{
public:
	enum State
	{
		Move,
		Attack,
		SlowDown,
		Bomber,
		Max
	};

	TutorialViewer();
	~TutorialViewer();

	void Update();
	void Draw();

	void Set(State state, const std::function<void()>& callback);

private:
	std::shared_ptr<float> textAlpha;
	std::shared_ptr<Polygon2D> bg;
	TextViewer *text;

	std::function<void()> callback;

	void _OnFinishFadeIn();
	std::function<void()> onFinisheFadeIn;
};
#endif