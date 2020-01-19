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

private:
	static const char* FileName[BGM_MAX];

};

#endif