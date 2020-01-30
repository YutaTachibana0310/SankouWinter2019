//=====================================
//
//ScoreRanking.h
//機能:スコアランキング
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _SCORERANKING_H_
#define _SCORERANKING_H_

#include "../../main.h"
#include "../System/RankingInfo.h"
#include <vector>

/**************************************
前方宣言
***************************************/

/**************************************
クラス定義
***************************************/
class ScoreRanking
{
public:
	ScoreRanking();
	~ScoreRanking();

	void CheckUpdate();

	std::vector<RankingInfo> GetRanking();
	static const unsigned RankingMax;

private:
	std::vector<RankingInfo> scoreContainer;
};
#endif