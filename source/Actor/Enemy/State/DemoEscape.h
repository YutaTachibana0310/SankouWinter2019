//=====================================
//
//DemoEscape.h
//�@�\:�f���G�l�~�[�����X�e�[�g
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _DEMOESCAPE_H_
#define _DEMOESCAPE_H_

#include "../../../../main.h"
#include "../../../../Framework/Pattern/BaseState.h"
#include "../DemoEnemyActor.h"

/**************************************
�O���錾
***************************************/

/**************************************
�N���X��`
***************************************/
class DemoEnemyActor::DemoEscape : public BaseState<DemoEnemyActor, DemoState>
{
public:
	void OnStart(DemoEnemyActor& entity);
	DemoState OnUpdate(DemoEnemyActor& entity);
};

#endif