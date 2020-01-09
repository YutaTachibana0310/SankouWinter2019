//=====================================
//
// ScoreViewer.h
// 機能:スコアビューワ
// Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _SCOREVIEWER_H_
#define _SCOREVIEWER_H_

#include "../../../main.h"

/**************************************
前方宣言
***************************************/
class TextViewer;

/**************************************
クラス定義
***************************************/
class ScoreViewer
{
public:
	ScoreViewer();
	~ScoreViewer();

	void Update();
	void Draw();

	void SetScore(int score);

private:
	TextViewer *caption;
	TextViewer *num;
};

#endif