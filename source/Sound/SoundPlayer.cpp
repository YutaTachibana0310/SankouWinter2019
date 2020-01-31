//=====================================
//
// SoundPlayer.cpp
// 機能:
// Author:GP12B332 21 立花雄太
//
//=====================================
#include "SoundPlayer.h"
#include "../../Framework/Sound/SoundEffect.h"

#define DEBUG_SOUND

/**************************************
グローバル変数
***************************************/
typedef struct
{
	std::string tag;
	std::string fileName;
	float volume;
} SoundData;

/**************************************
読み込み処理
***************************************/
void SoundPlayer::Load()
{
	std::vector<SoundData> datas =
	{
		{"PlayerShot", "gun25.wav", 0.2f},
		{"SmallExplosion", "smallExplosion.wav", 0.5f},
		{"MiddleExplosion", "middleExplosion.wav", 0.65f},
		{"BigExplosion", "bigExplosion.wav", 0.7f},
		{"Bomber", "magic-electron.wav", 0.7f},
		{"PowerUp", "shakin2.wav", 0.9f},
		{"Decide", "kettei-02.wav", 0.7f},
		{"TextIn", "iainuki1.wav", 0.5f},
		{"PlayerExplosion", "beamgun1.wav", 1.0f},
		{"Score", "decision2.wav", 0.15f},
		{"Slowdown", "magic-gravity1.wav", 0.8f},
		{"GameStart", "decision12.wav", 0.8f},
		{"StageClear", "stageClear.wav", 0.8f},
		{"GameOver", "Who_Are_You.wav", 0.8f}
	};

	const std::string directoryPath = "data/SOUND/SE/";

	size_t numSound = datas.size();
	for (size_t i = 0; i < numSound; i++)
	{
		std::string path = directoryPath;
		path += datas[i].fileName;

		SE::Load(path.c_str(), i);
		tagTable[datas[i].tag] = i;
		volumeTable[datas[i].tag] = datas[i].volume;
	}
}

/**************************************
再生処理
***************************************/
void SoundPlayer::Play(const std::string & tag)
{
#ifdef DEBUG_SOUND
	if (tagTable.count(tag) == 0)
		return;
#endif

	SE::Play(tagTable[tag], volumeTable[tag]);
}
