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

private:
	TimeBreakText *timeBreak;

	bool inPlaying;
};

#endif