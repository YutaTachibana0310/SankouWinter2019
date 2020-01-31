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
class Polygon2D;

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