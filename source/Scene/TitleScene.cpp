//=====================================
//
//TitleScene.cpp
//�@�\:�^�C�g���V�[��
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "TitleScene.h"
#include "../../Framework/Camera/Camera.h"

#include "../Viewer/Title/TitleViewer.h"
#include "../BackGround/GameSkybox.h"

/**************************************

***************************************/

/**************************************
����������
***************************************/
void TitleScene::Init()
{
	sceneCamera = new Camera();
	Camera::SetMainCamera(sceneCamera);

	viewer = new TitleViewer();
	skybox = new GameSkybox();
}

/**************************************
�I������
***************************************/
void TitleScene::Uninit()
{
	SAFE_DELETE(sceneCamera);
	SAFE_DELETE(viewer);
	SAFE_DELETE(skybox);
}

/**************************************
�X�V����
***************************************/
void TitleScene::Update()
{
	sceneCamera->Update();
	skybox->Update();
	viewer->Update();
}

/**************************************
�`�揈��
***************************************/
void TitleScene::Draw()
{
	sceneCamera->Set();
	skybox->Draw();
	viewer->Draw();
}
