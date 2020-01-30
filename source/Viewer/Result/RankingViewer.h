//=====================================
//
//RankingViewer.h
//�@�\:�����L���O�r���[��
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _RANKINGVIEWER_H_
#define _RANKINGVIEWER_H_

#include "../../../main.h"
#include "../../System/RankingInfo.h"
#include <vector>

/**************************************
�O���錾
***************************************/
class RankingText;
class RankingInfo;
class Polygon2D;

/**************************************
�N���X��`
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