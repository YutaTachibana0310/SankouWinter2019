//=====================================
//
//GameScore.h
//機能:ゲームスコア
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _GAMESCORE_H_
#define _GAMESCORE_H_

#include "../../main.h"
#include "../../Framework/Pattern/BaseSingleton.h"

/**************************************
前方宣言
***************************************/

/**************************************
クラス定義
締め切りがやばいのでシングルトンにしてしまう
本当はちゃんと設計したい
***************************************/
class GameScore : public BaseSingleton<GameScore>
{
public:
	void AddScore(unsigned int point);
	void AddCombo();

	unsigned int Score() const;

	void Init();

	void Save();

	void ResetCombo();

private:
	unsigned int score;
	unsigned int combo;
};
#endif