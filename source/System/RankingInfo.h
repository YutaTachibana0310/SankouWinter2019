//=====================================
//
//RankingInfo.h
//�@�\:�����L���O���
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _RANKINGINFO_H_
#define _RANKINGINFO_H_

#include "../../main.h"

/**************************************
�O���錾
***************************************/

/**************************************
�N���X��`
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