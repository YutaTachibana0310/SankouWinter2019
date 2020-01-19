//=====================================
//
// SoundPlayer.h
// �@�\:���ʉ��Đ��N���X
// Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _SOUNDPLAYER_H_
#define _SOUNDPLAYER_H_

#include "../../main.h"
#include "../../Framework/Pattern/BaseSingleton.h"

#include <unordered_map>

/**************************************
�O���錾
***************************************/

/**************************************
�N���X��`
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