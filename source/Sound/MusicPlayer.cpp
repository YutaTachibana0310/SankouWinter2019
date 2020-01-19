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
};

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
	BGM::Play(id, 0.7f);
}
