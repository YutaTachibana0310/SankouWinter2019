//=====================================
//
// GameInput.cpp
// 機能:
// Author:GP12B332 21 立花雄太
//
//=====================================
#include "GameInput.h"
#include "../../Framework/Input/input.h"

/**************************************
グローバル変数
***************************************/

/**************************************
ショットボタン入力
***************************************/
bool GameInput::GetShotButtonPress()
{
	return Keyboard::GetPress(DIK_Z);
}

/**************************************
ボンバーボタン入力
***************************************/
bool GameInput::GetBomberButtonTrigger()
{
	return Keyboard::GetTrigger(DIK_X);
}

/**************************************
スロウダウンボタン入力
***************************************/
bool GameInput::GetSlowdownButtonPress()
{
	return Keyboard::GetPress(DIK_C);
}
