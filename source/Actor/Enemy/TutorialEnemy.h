//=====================================
//
//TutorialEnemy.h
//�@�\:�`���[�g���A���p�G�l�~�[
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _TUTORIALENEMY_H_
#define _TUTORIALENEMY_H_

#include "../../../main.h"
#include "Base\BaseMiddleEnemy.h"

/**************************************
�O���錾
***************************************/
class BaseEmitter;

/**************************************
�N���X��`
***************************************/
class TutorialEnemyActor : public BaseMiddleEnemy
{
public:
	TutorialEnemyActor(EnemyEventHandler* handler);
	~TutorialEnemyActor();

	void Init();
	void Uninit();
	void Update();
	void Draw();

private:
	std::shared_ptr<Transform> shotTransformLeft;
	std::shared_ptr<Transform> shotTransformRight;

	float cntFrame;
	int cntAttack;

	bool enableAttack;

	BaseEmitter *trailEmitterR;
	BaseEmitter *trailEmitterL;

	void ChangeState(int next);
};
#endif