//=====================================
//
// SoundPlayer.h
// 機能:効果音再生クラス
// Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _SOUNDPLAYER_H_
#define _SOUNDPLAYER_H_

#include "../../main.h"
#include "../../Framework/Pattern/BaseSingleton.h"

#include <unordered_map>

/**************************************
前方宣言
***************************************/

/**************************************
クラス定義
***************************************/
class SoundPlayer : public BaseSingleton<SoundPlayer>
{
public:
	void Load();

	void Play(const std::string& tag);

private:
	std::unordered_map<std::string, int> tagTable;
	std::unordered_map<std::string, float> volumeTable;
};

#endif