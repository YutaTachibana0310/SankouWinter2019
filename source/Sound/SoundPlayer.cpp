//=====================================
//
// SoundPlayer.cpp
// �@�\:
// Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "SoundPlayer.h"
#include "../../Framework/Sound/SoundEffect.h"

#define DEBUG_SOUND

/**************************************
�O���[�o���ϐ�
***************************************/
typedef struct
{
	std::string tag;
	std::string fileName;
	float volume;
} SoundData;

/**************************************
�ǂݍ��ݏ���
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
�Đ�����
***************************************/
void SoundPlayer::Play(const std::string & tag)
{
#ifdef DEBUG_SOUND
	if (tagTable.count(tag) == 0)
		return;
#endif

	SE::Play(tagTable[tag], volumeTable[tag]);
}
