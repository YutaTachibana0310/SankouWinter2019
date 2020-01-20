//=====================================
//
// BaseBigEnemy.h
// 機能:大型エネミー基底クラス
// Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _BASEBIGENEMY_H_
#define _BASEBIGENEMY_H_

#include "../../../../main.h"
#include "BaseEnemy.h"

/**************************************
前方宣言
***************************************/

/**************************************
クラス定義
***************************************/
class BaseBigEnemy : public BaseEnemy
{
public:
	BaseBigEnemy(EnemyEventHandler* handler);

	virtual void Uninit();

	void Explode();
	EnemyType GetType();

	virtual bool IsDestroied() override;

protected:
	bool isDestroied;
};

#endif