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
	transform->LookAt(Vector3::Zero);
}

/**************************************
�f�X�g���N�^
***************************************/
GameCamera::~GameCamera()
{
}
