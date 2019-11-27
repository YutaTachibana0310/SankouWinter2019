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
	LoadTexture("data/TEXTURE/Skybox/WorldSkyBox02bBack.jpg", Surface::Back);
	LoadTexture("data/TEXTURE/Skybox/WorldSkyBox02bFront.jpg", Surface::Front);
	LoadTexture("data/TEXTURE/Skybox/WorldSkyBox02bRight.jpg", Surface::Right);
	LoadTexture("data/TEXTURE/Skybox/WorldSkyBox02bLeft.jpg", Surface::Left);
	LoadTexture("data/TEXTURE/Skybox/WorldSkyBox02bUp.jpg", Surface::Up);
	LoadTexture("data/TEXTURE/Skybox/WorldSkyBox02bDown.jpg", Surface::Down);
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
	transform->Rotate(-0.050f, Vector3::Up);
}
