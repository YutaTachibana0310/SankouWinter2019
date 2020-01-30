//=====================================
//
//ScoreRanking.h
//�@�\:�X�R�A�����L���O
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _SCORERANKING_H_
#define _SCORERANKING_H_

#include "../../main.h"
#include "../System/RankingInfo.h"
#include <vector>

/**************************************
�O���錾
***************************************/

/**************************************
�N���X��`
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