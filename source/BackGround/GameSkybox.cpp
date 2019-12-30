//=====================================
//
//GameSkybox.cpp
//�@�\:
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "GameSkybox.h"

/**************************************
�R���X�g���N�^
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
�f�X�g���N�^
***************************************/
GameSkybox::~GameSkybox()
{
}

/**************************************
�X�V����
***************************************/
void GameSkybox::Update()
{
	transform->Rotate(-0.01f, Vector3::Up);
}
