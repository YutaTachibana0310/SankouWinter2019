//=====================================
//
//Light.h
//機能:ライト
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _LIGHT_H_
#define _LIGHT_H_

#include "../../main.h"

#define NUM_LIGHT (3)

/**************************************
前方宣言
***************************************/

/**************************************
クラス定義
***************************************/
namespace Light
{
	void Init();
	void Update();

	D3DLIGHT9 GetData(int id);

	int LightMax();
}

#endif