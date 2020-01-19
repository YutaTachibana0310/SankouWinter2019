//=====================================
//
// GameInput.h
// �@�\:�Q�[�����͏���
// Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _GAMEINPUT_H_
#define _GAMEINPUT_H_

#include "../../main.h"

/**************************************
�O���錾
***************************************/

/**************************************
�N���X��`
***************************************/
class GameInput
{
private:
	GameInput() {}
	~GameInput() {}

public:
	static bool GetShotButtonPress();
	static bool GetBomberButtonTrigger();
	static bool GetSlowdownButtonPress();
};

#endif