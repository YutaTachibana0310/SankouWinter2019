//=====================================
//
//GameCamera.cpp
//�@�\:
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "GameCamera.h"

/**************************************
�R���X�g���N�^
***************************************/
GameCamera::GameCamera()
{
	const D3DXVECTOR3 InitPos = { 50.0f, 0.0f, 0.0f };
	transform->SetPosition(InitPos);
}

/**************************************
�f�X�g���N�^
***************************************/
GameCamera::~GameCamera()
{
}
