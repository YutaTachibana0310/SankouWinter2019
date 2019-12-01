//=====================================
//
//GameCamera.cpp
//機能:
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "GameCamera.h"

/**************************************
コンストラクタ
***************************************/
GameCamera::GameCamera()
{
	const D3DXVECTOR3 InitPos = { 50.0f, 0.0f, 0.0f };
	transform->SetPosition(InitPos);
	transform->LookAt(Vector3::Zero);
}

/**************************************
デストラクタ
***************************************/
GameCamera::~GameCamera()
{
}
