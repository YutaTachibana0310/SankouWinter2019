//=====================================
//
// FixedTime.h
// �@�\:���̃V�X�e���̌Œ莞�ԊǗ��N���X
// Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _FIEXEDTIME_H_
#define _FIEXEDTIME_H_

#include "../../main.h"

/**************************************
�O���錾
***************************************/

/**************************************
�N���X��`
***************************************/
class FixedTime
{
	friend class BaseGame;
	friend class SceneManager;
public:
	static inline void SetTimeScale(float scale)
	{
		timeScale = scale;
	}

	static inline float GetTimeScale()
	{
		return timeScale;
	}

private:
	static float timeScale;
};

#endif