//=====================================
//
//GameScene.cpp
//�@�\:�Q�[���V�[������
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "GameScene.h"
#include "../../Framework/Camera/Camera.h"
#include "../../Framework/Resource/ResourceManager.h"

#include "../BackGround/GameSkybox.h"
#include "../Actor/PlayerActor.h"

/**************************************
����������
***************************************/
void GameScene::Init()
{
	ResourceManager::Instance()->LoadMesh("Player", "data/MODEL/Player/Player.x");

	sceneCamera = new Camera();
	skybox = new GameSkybox();
	player = new PlayerActor();

	Camera::SetMainCamera(sceneCamera);
}

/**************************************
�I������
***************************************/
void GameScene::Uninit()
{
	SAFE_DELETE(sceneCamera);
	SAFE_DELETE(skybox);
	SAFE_DELETE(player);
}

/**************************************
�X�V����
***************************************/
void GameScene::Update()
{
	sceneCamera->Update();
	skybox->Update();
	player->Update();
}

/**************************************
�`�揈��
***************************************/
void GameScene::Draw()
{
	Camera::MainCamera()->Set();

	skybox->Draw();

	player->Draw();
}