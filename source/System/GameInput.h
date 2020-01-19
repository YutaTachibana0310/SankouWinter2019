//=====================================
//
// GameInput.h
// 機能:ゲーム入力処理
// Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _GAMEINPUT_H_
#define _GAMEINPUT_H_

#include "../../main.h"

/**************************************
前方宣言
***************************************/

/**************************************
クラス定義
***************************************/
class GameInput
{
private:
	GameInput() {}
	~GameInput() {}

public:
	static bool GetShotButtonPress();
	static bool GetBomberButtonTrigger();
	static bool GetSlowdownButtonPress();
};

#endif