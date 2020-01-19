//=====================================
//
//BaseSmallEnemy.h
//機能:小型エネミー基底クラス
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _BASESMALLENEMY_H_
#define _BASESMALLENEMY_H_

#include "../../../../main.h"
#include "BaseEnemy.h"

/**************************************
前方宣言
***************************************/

/**************************************
クラス定義
***************************************/
class BaseSmallEnemy : public BaseEnemy
{
	using BaseEnemy::BaseEnemy;
public:
	void Explode();

	EnemyType GetType();
};

#endif