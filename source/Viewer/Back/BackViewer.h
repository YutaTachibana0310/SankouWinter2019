//=====================================
//
//BackViewer.h
//�@�\:�w�iUI�r���[��
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _BACKVIEWER_H_
#define _BACKVIEWER_H_

#include "../../../main.h"
#include <vector>

/**************************************
�O���錾
***************************************/
class TimeBreakText;
class Polygon2D;

/**************************************
�N���X��`
***************************************/
class BackViewer
{
public:
	BackViewer();
	~BackViewer();

	void Draw();

	enum ViewerID
	{
		TimeBreakUpper,
		TimeBreakLower,
		ViewerMax
	};

	void PlayTimeBreak();
	void PlayPowerUp();
	void PlayBeatEnemy();
	void PlayFireBom();
	void SetGreenBG(bool state);

private:
	TimeBreakText *timeBreak;
	std::shared_ptr<Polygon2D> greenBG;

	bool inPlaying;

	bool greenBGstate;
};

#endif