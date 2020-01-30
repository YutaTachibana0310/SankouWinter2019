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
#include "../System/ScoreRanking.h"
#include "../Viewer/Result/RankingViewer.h"

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
	ranking = new ScoreRanking();
	rankViewer = new RankingViewer();

	ranking->CheckUpdate();

	auto rankingContainer = ranking->GetRanking();
	rankViewer->SetRanking(rankingContainer);
}

/**************************************
�I������
***************************************/
void ResultScene::Uninit()
{
	SAFE_DELETE(sceneCamera);
	SAFE_DELETE(viewer);
	SAFE_DELETE(ranking);
	SAFE_DELETE(rankViewer);
}

/**************************************
�X�V����
***************************************/
void ResultScene::Update()
{
	sceneCamera->Update();
	viewer->Update();
	rankViewer->Update();
}

/**************************************
�`�揈��
***************************************/
void ResultScene::Draw()
{
	sceneCamera->Set();
	viewer->Draw();
	rankViewer->Draw();
}
