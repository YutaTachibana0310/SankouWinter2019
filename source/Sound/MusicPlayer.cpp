//=====================================
//
// MusicPlayer.cpp
// �@�\:
// Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "MusicPlayer.h"
#include "../../Framework/Sound/BackgroundMusic.h"

/**************************************
�O���[�o���ϐ�
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
�ǂݍ��ݏ�������
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
�Đ�����
***************************************/
void MusicPlayer::PlayBGM(BGM_ID id)
{
	current = id;
	BGM::Play(id, 0.7f);
}

/**************************************
�t�F�[�h�C������
***************************************/
void MusicPlayer::FadeIn(BGM_ID id, int duration)
{
	current = id;
	BGM::FadeIn(id, 0.7f, duration, false);
}

/**************************************
�t�F�[�h�A�E�g����
***************************************/
void MusicPlayer::FadeOut(int duration)
{
	BGM::Fade(current, 0.0f, duration, false);
}
