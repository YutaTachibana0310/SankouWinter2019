//=====================================
//
//SnipeInit.h
//�@�\:�X�i�C�v�G�l�~�[�����X�e�[�g
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _SNIPEINIT_H_
#define _SNIPEINIT_H_

#include "../../../../main.h"
#include "../SnipeEnemyActor.h"

/**************************************
�O���錾
***************************************/

/**************************************
�N���X��`
***************************************/
class SnipeEnemyActor::SnipeInit : public BaseState<SnipeEnemyActor, SnipeEnemyActor::SnipeState>
{
public:
	void OnStart(SnipeEnemyActor& entity);
	SnipeState OnUpdate(SnipeEnemyActor& entity);
};
#endif