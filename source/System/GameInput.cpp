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
	return Keyboard::GetPress(DIK_Z);
}

/**************************************
�{���o�[�{�^������
***************************************/
bool GameInput::GetBomberButtonTrigger()
{
	return Keyboard::GetTrigger(DIK_X);
}

/**************************************
�X���E�_�E���{�^������
***************************************/
bool GameInput::GetSlowdownButtonPress()
{
	return Keyboard::GetPress(DIK_C);
}
