//=====================================
//
//TutorialMove.h
//�@�\:�ړ��`���[�g���A��
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _TUTORIALMOVE_H_
#define _TUTORIALMOVE_H_

#include "../../../main.h"
#include "../TutorialScene.h"

/**************************************
�O���錾
***************************************/

/**************************************
�N���X��`
***************************************/
class TutorialScene::TutorialMove : public TutorialScene::TutorialState
{
public:
	void OnStart(TutorialScene& entity);
	State OnUpdate(TutorialScene& entity);
};
#endif