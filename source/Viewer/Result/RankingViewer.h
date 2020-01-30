//=====================================
//
//RankingViewer.h
//機能:ランキングビューワ
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _RANKINGVIEWER_H_
#define _RANKINGVIEWER_H_

#include "../../../main.h"
#include "../../System/RankingInfo.h"
#include <vector>

/**************************************
前方宣言
***************************************/
class RankingText;
class RankingInfo;
class Polygon2D;

/**************************************
クラス定義
***************************************/
class RankingViewer
{
public:
	RankingViewer();
	~RankingViewer();

	void Update();
	void Draw();

	void SetRanking(const std::vector<RankingInfo>& ranking);

private:
	std::vector<RankingText*> rankingContainer;

	Polygon2D *caption;
};

#endif