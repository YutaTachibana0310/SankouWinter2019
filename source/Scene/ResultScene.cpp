//=====================================
//
//ResultScene.cpp
//�@�\:���U���g�V�[��
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "ResultScene.h"
#include "../../Framework/Camera/Camera.h"

#include "../Viewer/Result/ResultViewer.h"

/**************************************
�O���[�o���ϐ�
***************************************/

/**************************************
����������
***************************************/
void ResultScene::Init()
{
	sceneCamera = new Camera();
	Camera::SetMainCamera(sceneCamera);

	viewer = new ResultViewer();
}

/**************************************
�I������
***************************************/
void ResultScene::Uninit()
{
	SAFE_DELETE(sceneCamera);
	SAFE_DELETE(viewer);
}

/**************************************
�X�V����
***************************************/
void ResultScene::Update()
{
	sceneCamera->Update();
	viewer->Update();
}

/**************************************
�`�揈��
***************************************/
void ResultScene::Draw()
{
	sceneCamera->Set();
	viewer->Draw();
}
