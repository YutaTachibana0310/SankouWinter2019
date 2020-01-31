//=====================================
//
// MusicPlayer.h
// 機能:ミュージックプレイヤー
// Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _MUSICPLAYER_H_
#define _MUSICPLAYER_H_

#include "../../main.h"

/**************************************
前方宣言
***************************************/
enum BGM_ID
{
	GameBGM,
	ResultBGM,
	TutorialBGM,
	TitleBGM,
	BGM_MAX
};

/**************************************
クラス定義
***************************************/
class MusicPlayer
{
public:
	static void Load();
	static void PlayBGM(BGM_ID id);
	static void FadeIn(BGM_ID id, int duration);
	static void FadeOut(int duration);

private:
	static const char* FileName[BGM_MAX];
	static BGM_ID current;
};

#endif