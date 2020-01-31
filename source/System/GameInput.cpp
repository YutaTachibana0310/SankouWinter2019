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
	return Keyboard::GetPress(DIK_Z) || GamePad::GetPress(0, BUTTON_A);
}

/**************************************
ボンバーボタン入力
***************************************/
bool GameInput::GetBomberButtonTrigger()
{
	return Keyboard::GetTrigger(DIK_X) || GamePad::GetTrigger(0, BUTTON_B);
}

/**************************************
スロウダウンボタン入力
***************************************/
bool GameInput::GetSlowdownButtonPress()
{
	return Keyboard::GetPress(DIK_C) || GamePad::GetPress(0, BUTTON_Z);
}

/**************************************
スロウダウンボタントリガー入力
***************************************/
bool GameInput::GetSlowdownButtonTrigger()
{
	return Keyboard::GetTrigger(DIK_C) || GamePad::GetTrigger(0, BUTTON_Z);
}
