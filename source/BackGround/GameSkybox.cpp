//=====================================
//
//GameSkybox.cpp
//機能:
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "GameSkybox.h"

/**************************************
コンストラクタ
***************************************/
GameSkybox::GameSkybox() : 
	SkyBox({10000.0f, 10000.0f, 10000.0f})
{
	LoadTexture("data/TEXTURE/Skybox/BlueNebular_back.jpg", Surface::Back);
	LoadTexture("data/TEXTURE/Skybox/BlueNebular_front.jpg", Surface::Front);
	LoadTexture("data/TEXTURE/Skybox/BlueNebular_left.jpg", Surface::Right);
	LoadTexture("data/TEXTURE/Skybox/BlueNebular_right.jpg", Surface::Left);
	LoadTexture("data/TEXTURE/Skybox/BlueNebular_top.jpg", Surface::Up);
	LoadTexture("data/TEXTURE/Skybox/BlueNebular_bottom.jpg", Surface::Down);
}

/**************************************
デストラクタ
***************************************/
GameSkybox::~GameSkybox()
{
}

/**************************************
更新処理
***************************************/
void GameSkybox::Update()
{
	transform->Rotate(-0.01f, Vector3::Up);
}
