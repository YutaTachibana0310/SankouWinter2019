//=====================================
//
//EnemyTimeController.h
//�@�\:�G�l�~�[�^�C���R���g���[��
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _ENEMYTIMECONTROLLER_H_
#define _ENEMYTIMECONTROLLER_H_

#include "../../main.h"

/**************************************
�O���錾
***************************************/

/**************************************
�N���X��`
***************************************/
class EnemyTimeController
{
public:
	static float GetTimeScale();
	static void SetTimeScale(float scale);

private:
	static float timeScale;
};

#endif