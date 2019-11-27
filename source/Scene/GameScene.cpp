//=====================================
//
//GameScene.cpp
//�@�\:�Q�[���V�[������
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "GameScene.h"
#include "../../Framework/Camera/Camera.h"

#include "../BackGround/GameSkybox.h"

/**************************************
����������
***************************************/
void GameScene::Init()
{
	sceneCamera = new Camera();
	skybox = new GameSkybox();

	Camera::SetMainCamera(sceneCamera);
}

/**************************************
�I������
***************************************/
void GameScene::Uninit()
{
	SAFE_DELETE(sceneCamera);
	SAFE_DELETE(skybox);
}

/**************************************
�X�V����
***************************************/
void GameScene::Update()
{
	sceneCamera->Update();
	skybox->Update();
}

/**************************************
�`�揈��
***************************************/
void GameScene::Draw()
{
	Camera::MainCamera()->Set();

	skybox->Draw();
}