//=====================================
//
//GameScore.cpp
//機能:ゲームスコア
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "GameScore.h"
#include "../../Framework/Core/PlayerPrefs.h"
#include "../GameConfig.h"

/**************************************
スコア加算処理
***************************************/
void GameScore::AddScore(unsigned int point)
{
	score += point;
}

/**************************************
スコア取得処理
***************************************/
unsigned int GameScore::Score() const
{
	return score;
}

/**************************************
初期化処理
***************************************/
void GameScore::Init()
{
	score = 0;
}

/**************************************
セーブ処理
***************************************/
void GameScore::Save()
{
	std::string saveKey = std::string(NAMEOF_ENUM(GameConfig::SaveKey::CurrentScore));
	PlayerPrefs::SaveNumber<unsigned int>(saveKey, score);
}
