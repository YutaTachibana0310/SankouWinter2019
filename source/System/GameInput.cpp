//=====================================
//
// GameInput.cpp
// �@�\:
// Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "GameInput.h"
#include "../../Framework/Input/input.h"

/**************************************
�O���[�o���ϐ�
***************************************/

/**************************************
�V���b�g�{�^������
***************************************/
bool GameInput::GetShotButtonPress()
{
	return Keyboard::GetPress(DIK_Z) || GamePad::GetPress(0, BUTTON_A);
}

/**************************************
�{���o�[�{�^������
***************************************/
bool GameInput::GetBomberButtonTrigger()
{
	return Keyboard::GetTrigger(DIK_X) || GamePad::GetTrigger(0, BUTTON_B);
}

/**************************************
�X���E�_�E���{�^������
***************************************/
bool GameInput::GetSlowdownButtonPress()
{
	return Keyboard::GetPress(DIK_C) || GamePad::GetPress(0, BUTTON_Z);
}

/**************************************
�X���E�_�E���{�^���g���K�[����
***************************************/
bool GameInput::GetSlowdownButtonTrigger()
{
	return Keyboard::GetTrigger(DIK_C) || GamePad::GetTrigger(0, BUTTON_Z);
}
