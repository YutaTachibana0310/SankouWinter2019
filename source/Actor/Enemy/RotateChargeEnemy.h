//=====================================
//
//RotateChargeEnemy.h
//機能:回転して突進するエネミー
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _ROTATECHARGEENEMYACTOR_H_
#define _ROTATECHARGEENEMYACTOR_H_

#include "../../../main.h"
#include "Base\BaseSmallEnemy.h"

/**************************************
前方宣言
***************************************/
class MeshContainer;
class BaseEmitter;

/**************************************
クラス定義
***************************************/
class RotateChargeEnemy : public BaseSmallEnemy
{
public:
	RotateChargeEnemy(EnemyEventHandler* handler);
	~RotateChargeEnemy();

	virtual void Init() override;

	virtual void Uninit() override;

	virtual void Update() override;

	virtual void Draw() override;

	void ChangeState(int next) {}

	void Explode() override;

private:
	bool enableHoming;
	BaseEmitter *trailEmitter;
};

#endif