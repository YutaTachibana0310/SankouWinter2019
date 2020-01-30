//=====================================
//
//TutorialEnemy.h
//機能:チュートリアル用エネミー
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _TUTORIALENEMY_H_
#define _TUTORIALENEMY_H_

#include "../../../main.h"
#include "Base\BaseMiddleEnemy.h"

/**************************************
前方宣言
***************************************/
class BaseEmitter;

/**************************************
クラス定義
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