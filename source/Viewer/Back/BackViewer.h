//=====================================
//
//BackViewer.h
//機能:背景UIビューワ
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _BACKVIEWER_H_
#define _BACKVIEWER_H_

#include "../../../main.h"
#include <vector>

/**************************************
前方宣言
***************************************/
class TimeBreakText;

/**************************************
クラス定義
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