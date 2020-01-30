//=====================================
//
//RankingInfo.h
//機能:ランキング情報
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _RANKINGINFO_H_
#define _RANKINGINFO_H_

#include "../../main.h"

/**************************************
前方宣言
***************************************/

/**************************************
クラス定義
***************************************/
class RankingInfo
{
public:
	RankingInfo(int rank, unsigned int score, bool isPlayerScore) :
		rank(rank),
		score(score),
		isPlayerScore(isPlayerScore)
	{

	}

	int Rank() const
	{
		return rank;
	}

	unsigned int Score() const
	{
		return score;
	}

	bool IsPlayerScore() const
	{
		return isPlayerScore;
	}

private:
	int rank;
	unsigned int score;
	bool isPlayerScore;

};
#endif