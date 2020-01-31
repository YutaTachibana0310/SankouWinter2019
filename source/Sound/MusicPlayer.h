//=====================================
//
// MusicPlayer.h
// �@�\:�~���[�W�b�N�v���C���[
// Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _MUSICPLAYER_H_
#define _MUSICPLAYER_H_

#include "../../main.h"

/**************************************
�O���錾
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
�N���X��`
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