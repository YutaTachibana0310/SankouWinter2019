//=====================================
//
//SnipeEscape.h
//�@�\:�X�i�C�v�G�l�~�[�����X�e�[�g
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _SNIPEESCAPE_H_
#define _SNIPEESCAPE_H_

#include "../../../../main.h"
#include "../SnipeEnemyActor.h"

/**************************************
�O���錾
***************************************/

/**************************************
�N���X��`
***************************************/
class SnipeEnemyActor::SnipeEscape : public BaseState<SnipeEnemyActor, SnipeState>
{
public:
	void OnStart(SnipeEnemyActor& entity);
	SnipeState OnUpdate(SnipeEnemyActor& entity);
};

#endif