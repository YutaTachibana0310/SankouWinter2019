//=====================================
//
//RankingText.h
//機能:ランキングテキスト
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _RANKINGTEXT_H_
#define _RANKINGTEXT_H_

#include "../../../main.h"
#include "../../../Framework/Renderer2D/TextViewer.h"
#include <vector>

/**************************************
前方宣言
***************************************/
class RankingInfo;

/**************************************
クラス定義
***************************************/
class RankingText : public TextViewer
{
public:
	RankingText();
	~RankingText();

	void MoveIn(float delay);

	void SetScore(const RankingInfo& info);

private:

};
#endif