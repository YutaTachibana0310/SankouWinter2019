//=====================================
//
// MusicPlayer.cpp
// 機能:
// Author:GP12B332 21 立花雄太
//
//=====================================
#include "MusicPlayer.h"
#include "../../Framework/Sound/BackgroundMusic.h"

/**************************************
グローバル変数
***************************************/
const char* MusicPlayer::FileName[BGM_MAX]
{
	"Ro-Crazy.wav",
	"Traffic_Jam.wav",
	"DETROIT_BEAT.wav",
	"Go_Ahead.wav",
};

BGM_ID MusicPlayer::current = BGM_MAX;

/**************************************
読み込み処理処理
***************************************/
void MusicPlayer::Load()
{
	for (int i = 0; i < BGM_MAX; i++)
	{
		std::string path = "data/SOUND/BGM/" + std::string(FileName[i]);
		BGM::Load(path.c_str(), i);
	}
}

/**************************************
再生処理
***************************************/
void MusicPlayer::PlayBGM(BGM_ID id)
{
	current = id;
	BGM::Play(id, 0.7f);
}

/**************************************
フェードイン処理
***************************************/
void MusicPlayer::FadeIn(BGM_ID id, int duration)
{
	current = id;
	BGM::FadeIn(id, 0.7f, duration, false);
}

/**************************************
フェードアウト処理
***************************************/
void MusicPlayer::FadeOut(int duration)
{
	BGM::Fade(current, 0.0f, duration, false);
}
