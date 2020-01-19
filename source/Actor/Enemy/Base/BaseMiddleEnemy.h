//=====================================
//
// BaseMiddleEnemy.h
// 機能:中型エネミー基底クラス
// Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _BASEMIDDLENEMY_H_
#define _BASEMIDDLENEMY_H_

#include "../../../../main.h"
#include "BaseEnemy.h"

/**************************************
前方宣言
***************************************/

/**************************************
クラス定義
***************************************/
class BaseMiddleEnemy : public BaseEnemy
{
public:
	void Explode();
	EnemyType GetType();
};

#endif